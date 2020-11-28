#include <algorithms.h>

// TODO binary search
int indexOfSorted_size_t(size_t val, size_t *arr, int arrLen)
{
    int index = 0;
    while (arrLen)
    {
        if (*arr == val)
            return index;
        arrLen--;
        arr++;
        index++;
    }
    return -1;
}
