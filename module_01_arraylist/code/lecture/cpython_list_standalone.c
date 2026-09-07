/*
 * A stand-alone teaching extraction of CPython's array-backed list.
 *
 * Derived from CPython 3.12.11:
 *   Include/cpython/listobject.h
 *   Objects/listobject.c
 *
 * CPython is distributed under the Python Software Foundation License.
 * This file is an adaptation, not a byte-for-byte copy: interpreter object
 * headers, exceptions, the GIL, garbage collection, and allocator APIs are
 * replaced with small stand-alone equivalents so this file compiles alone.
 * The representation, resize policy, insertion shift, deletion shift,
 * sublist creation, and reference-ownership behavior follow the corresponding
 * CPython mechanisms.
 *
 * Build:
 *   cc -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow \
 *      cpython_list_standalone.c -o cpython_list_standalone
 *
 * Invariant:
 *   0 <= size <= allocated
 *   ob_item points to allocated pointer slots, or is NULL when allocated == 0
 *   ob_item[0..size-1] are owned references to live objects
 */

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PyObject {
    const char *text;
    size_t refcount;
};

/* Teaching equivalent of the relevant fields in CPython's PyListObject. */
struct PyListObject {
    struct PyObject **ob_item;
    size_t size;       /* Number of active elements. */
    size_t allocated;  /* Number of pointer slots in ob_item. */
};

static void Py_INCREF(struct PyObject *object)
{
    object->refcount += 1U;
}

static void Py_DECREF(struct PyObject *object)
{
    assert(object->refcount > 0U);
    object->refcount -= 1U;
}

static int list_invariant(const struct PyListObject *self)
{
    return self != NULL && self->size <= self->allocated &&
        ((self->allocated == 0U) == (self->ob_item == NULL));
}

/* Adapted from CPython's list_resize(). */
static int list_resize(struct PyListObject *self, size_t newsize)
{
    size_t new_allocated;
    size_t oldsize;
    struct PyObject **items;

    assert(list_invariant(self));
    oldsize = self->size;

    /* Reuse the current allocation unless the list fell below half full. */
    if (self->allocated >= newsize && newsize >= (self->allocated >> 1U)) {
        self->size = newsize;
        return 0;
    }

    /* CPython 3.12 overallocation: roughly 12.5%, rounded to a multiple of 4. */
    if (newsize > SIZE_MAX - (newsize >> 3U) - 6U) {
        return -1;
    }
    new_allocated = (newsize + (newsize >> 3U) + 6U) & ~(size_t)3U;

    /* Avoid extra spare space after one unusually large extension. */
    if (newsize > oldsize &&
        newsize - oldsize > new_allocated - newsize) {
        new_allocated = (newsize + 3U) & ~(size_t)3U;
    }
    if (newsize == 0U) {
        new_allocated = 0U;
    }
    if (new_allocated > SIZE_MAX / sizeof(*self->ob_item)) {
        return -1;
    }

    if (new_allocated == 0U) {
        free(self->ob_item);
        self->ob_item = NULL;
    } else {
        items = realloc(self->ob_item, new_allocated * sizeof(*items));
        if (items == NULL && newsize < oldsize) {
            /* Keep the larger allocation: logically shrinking cannot fail. */
            self->size = newsize;
            return 0;
        }
        if (items == NULL) {
            return -1;
        }
        self->ob_item = items;
    }

    self->size = newsize;
    self->allocated = new_allocated;
    assert(list_invariant(self));
    return 0;
}

static void PyList_Init(struct PyListObject *self)
{
    self->ob_item = NULL;
    self->size = 0U;
    self->allocated = 0U;
}

/* Like the public CPython append operation, this stores a new reference. */
static int PyList_Append(struct PyListObject *self, struct PyObject *item)
{
    size_t oldsize;

    assert(list_invariant(self));
    if (item == NULL || self->size == SIZE_MAX) {
        return -1;
    }
    oldsize = self->size;
    if (list_resize(self, oldsize + 1U) < 0) {
        return -1;
    }
    Py_INCREF(item);
    self->ob_item[oldsize] = item;
    return 0;
}

/* Adapted from CPython's ins1(): negative and large indexes are normalized. */
static int PyList_Insert(
    struct PyListObject *self,
    ptrdiff_t where,
    struct PyObject *item
)
{
    size_t index;
    size_t oldsize;

    assert(list_invariant(self));
    if (item == NULL || self->size == SIZE_MAX) {
        return -1;
    }
    oldsize = self->size;
    if (list_resize(self, oldsize + 1U) < 0) {
        return -1;
    }

    if (where < 0) {
        where += (ptrdiff_t)oldsize;
        if (where < 0) {
            where = 0;
        }
    }
    index = (size_t)where;
    if (index > oldsize) {
        index = oldsize;
    }

    /* Copy backward so an element is not overwritten before it is copied. */
    for (size_t i = oldsize; i > index; i -= 1U) {
        self->ob_item[i] = self->ob_item[i - 1U];
    }
    Py_INCREF(item);
    self->ob_item[index] = item;
    return 0;
}

/* Teaching-sized equivalent of deleting one list element. */
static int PyList_Delete(struct PyListObject *self, size_t index)
{
    struct PyObject *removed;
    size_t oldsize;

    assert(list_invariant(self));
    if (index >= self->size) {
        return -1;
    }
    oldsize = self->size;
    removed = self->ob_item[index];

    if (index + 1U < oldsize) {
        memmove(&self->ob_item[index], &self->ob_item[index + 1U],
                (oldsize - index - 1U) * sizeof(*self->ob_item));
    }
    if (list_resize(self, oldsize - 1U) < 0) {
        return -1; /* CPython's shrinking path is designed not to fail. */
    }
    Py_DECREF(removed);
    return 0;
}

/*
 * The capstone operation, adapted from CPython's list_slice().
 *
 * Copy the half-open range [low, high) into a new list. The running time and
 * additional space are both O(k), where k is the number of copied elements.
 * The objects themselves are shared, so each copied pointer gains a reference.
 */
int PyList_Sublist(
    const struct PyListObject *self,
    size_t low,
    size_t high,
    struct PyListObject *result
)
{
    size_t count;

    assert(list_invariant(self));
    if (result == NULL || result == self) {
        return -1;
    }
    PyList_Init(result);

    if (low > self->size) {
        low = self->size;
    }
    if (high > self->size) {
        high = self->size;
    }
    if (high < low) {
        high = low;
    }
    count = high - low;
    if (count == 0U) {
        return 0;
    }
    if (count > SIZE_MAX / sizeof(*result->ob_item)) {
        return -1;
    }

    /* CPython allocates the result once because its final length is known. */
    result->ob_item = malloc(count * sizeof(*result->ob_item));
    if (result->ob_item == NULL) {
        return -1;
    }
    result->size = count;
    result->allocated = count;

    for (size_t source = low, destination = 0U;
         source < high;
         source += 1U, destination += 1U) {
        struct PyObject *item = self->ob_item[source];
        Py_INCREF(item);
        result->ob_item[destination] = item;
    }
    assert(list_invariant(result));
    return 0;
}

static void PyList_Destroy(struct PyListObject *self)
{
    for (size_t i = 0U; i < self->size; i += 1U) {
        Py_DECREF(self->ob_item[i]);
    }
    free(self->ob_item);
    PyList_Init(self);
}

static void PyList_Print(const struct PyListObject *self)
{
    printf("size=%zu allocated=%zu [", self->size, self->allocated);
    for (size_t i = 0U; i < self->size; i += 1U) {
        printf("%s%s", i == 0U ? "" : ", ", self->ob_item[i]->text);
    }
    puts("]");
}

int main(void)
{
    struct PyListObject list;
    struct PyListObject sublist;
    struct PyObject ten = {"10", 1U};
    struct PyObject twenty = {"20", 1U};
    struct PyObject thirty = {"30", 1U};
    struct PyObject fifteen = {"15", 1U};

    PyList_Init(&list);
    if (PyList_Append(&list, &ten) < 0 ||
        PyList_Append(&list, &twenty) < 0 ||
        PyList_Append(&list, &thirty) < 0 ||
        PyList_Insert(&list, 1, &fifteen) < 0) {
        PyList_Destroy(&list);
        return EXIT_FAILURE;
    }
    PyList_Print(&list);

    if (PyList_Delete(&list, 2U) < 0) { /* Delete 20. */
        PyList_Destroy(&list);
        return EXIT_FAILURE;
    }
    PyList_Print(&list);

    /* Python equivalent: sublist = list[1:3], producing [15, 30]. */
    if (PyList_Sublist(&list, 1U, 3U, &sublist) < 0) {
        PyList_Destroy(&list);
        return EXIT_FAILURE;
    }
    PyList_Print(&sublist);

    /* Destroying the sublist releases its references, not the shared objects. */
    PyList_Destroy(&sublist);
    PyList_Destroy(&list);

    assert(ten.refcount == 1U && twenty.refcount == 1U);
    assert(thirty.refcount == 1U && fifteen.refcount == 1U);
    return EXIT_SUCCESS;
}
