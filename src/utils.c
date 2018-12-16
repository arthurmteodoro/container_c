//
// Created by arthur on 16/12/18.
//

#include "./include/utils.h"

void swap(void** a, void** b)
{
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(void** arr, int low, int high, int (*cmp)(const void*, const void*))
{
    void* pivot = arr[high];
    int i = low - 1;

    int j;
    for(j = low; j <= high-1; j++)
    {
        if(cmp(arr[j], pivot) < 0)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quicksort(void** arr, int low, int high, int (*cmp)(const void*, const void*))
{
    if(low < high)
    {
        int pi = partition(arr, low, high, cmp);
        quicksort(arr, low, pi-1, cmp);
        quicksort(arr, pi+1, high, cmp);
    }
}