#include <stdio.h>

int main(void)
{
        /* Declare fixed storage */
        int array[10] = {100, 200, 300, 400, 500, 0, 0, 0, 0, 0};
        int array_capacity = 10;

        /* Setup item count */
        int size = 5;

        /* Position to access item */
        int pos;

        pos = 1;

        /* Check number */
        if (pos >= 0 && pos < size) {
                /* Read data */
                int data = array[pos];
                printf("Read value: %d\n", data);

                /* Change data */
                array[pos] = 500;
        }

        /* Target value to find */
        int target = 300;

        /* Where the result will be saved */
        int index;

        for (index = 0; index < size; index = index + 1) {
                if (array[index] == target) {
                        break;
                }
        }
        printf("Search result index: %d\n", index);

        /* Check number */
        if (pos >= 0 && pos < size) {
                /* Shift data left */
                for (int i = pos + 1; i < size; i = i + 1) {
                        array[i - 1] = array[i];
                }

                /* Decrease count */
                size = size - 1;
        }

        /* Check number */
        if (pos >= 0 && pos <= size && size < array_capacity) {
                /* Shift data right */
                for (int i = size - 1; i >= pos; i = i - 1) {
                        array[i + 1] = array[i];
                }

                /* Save data */
                array[pos] = 600;

                /* Increase count */
                size = size + 1;
        }

        printf("Final size: %d\n", size);
        for (int i = 0; i < size; i = i + 1) {
                printf("array[%d] = %d\n", i, array[i]);
        }

        return 0;
}
