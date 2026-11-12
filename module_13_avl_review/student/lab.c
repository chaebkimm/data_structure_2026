#ifndef MODULE_13_SEARCH_SORT_LAB_C
#define MODULE_13_SEARCH_SORT_LAB_C

#define SEARCH_SORT_CAPACITY 64

int linear_search(const int values[], int n, int key) {
    for (int i = 0; i < n; ++i) {
        if (values[i] == key) return i;
    }
    return -1;
}

int binary_search_first(const int sorted[], int n, int key) {
    int lo = 0;
    int hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (sorted[mid] < key) lo = mid + 1;
        else hi = mid;
    }
    if (lo < n && sorted[lo] == key) return lo;
    return -1;
}

void insertion_sort(int values[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = values[i];
        int pos = i;
        while (pos > 0 && values[pos - 1] > key) {
            values[pos] = values[pos - 1];
            --pos;
        }
        values[pos] = key;
    }
}

static void merge_range(int values[], int scratch[], int lo, int hi) {
    if (hi - lo <= 1) return;
    int mid = lo + (hi - lo) / 2;
    merge_range(values, scratch, lo, mid);
    merge_range(values, scratch, mid, hi);
    int left = lo;
    int right = mid;
    int out = lo;
    while (left < mid && right < hi) {
        if (values[left] <= values[right]) scratch[out++] = values[left++];
        else scratch[out++] = values[right++];
    }
    while (left < mid) scratch[out++] = values[left++];
    while (right < hi) scratch[out++] = values[right++];
    for (int i = lo; i < hi; ++i) values[i] = scratch[i];
}

void merge_sort(int values[], int scratch[], int n) {
    merge_range(values, scratch, 0, n);
}

#endif
