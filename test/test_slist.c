//
// Created by arthur on 15/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "../src/include/slist.h"

void print_list_using_for(SList sList)
{
    int i;
    int list_size = size_slist(sList);
    printf("[");
    for(i = 0; i < list_size; i++)
    {
        int* value_read = (int*) get_slist(sList, i);
        if (i == list_size-1)
            printf("%d]\n", *value_read);
        else
            printf("%d, ", *value_read);
    }
}

void print_array(void** arr, int n)
{
    int i;
    printf("[");
    for(i = 0; i < n; i++)
    {
        int* value_read = (int*) arr[i];
        if (i == n-1)
            printf("%d]\n", *value_read);
        else
            printf("%d, ", *value_read);
    }
}

int cmpfunc (const void* a, const void* b) {
    int* x = (int*) a;
    int* y = (int*) b;
    return *x - *y;
}

int main() {
    int i;
    SList list = create_slist();

    printf("Inserting 10 elements in the list using append\n");
    for(i = 0; i < 10; i++)
    {
        int* value = (int*) malloc(sizeof(int));
        *value = i;
        append_slist(list, value);
    }
    printf("List after insertion: ");
    print_list_using_for(list);

    printf("\nPrepending value 1000 in the list\n");
    int* value = (int*) malloc(sizeof(int));
    *value = 1000;
    prepend_slist(list, value);
    printf("List after prepend: ");
    print_list_using_for(list);

    printf("\nInserting value 5000 in position 3 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 5000;
    insert_slist(list, 3, value);
    printf("List after insert: ");
    print_list_using_for(list);

    printf("\nInserting value 767 in final position (using list size) of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 767;
    insert_slist(list, size_slist(list), value);
    printf("List after insert: ");
    print_list_using_for(list);

    printf("\nSetting value 323 in position 6 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 323;
    set_slist(list, 6, value);
    printf("List after set: ");
    print_list_using_for(list);

    printf("\nRemoving position 4 of the list\n");
    remove_index_slist(list, 4);
    printf("List after removing position 4: ");
    print_list_using_for(list);

    printf("\nRemoving position 0 of the list\n");
    remove_index_slist(list, 0);
    printf("List after removing position 0: ");
    print_list_using_for(list);

    printf("\nRemoving the last element of the list\n");
    remove_index_slist(list, size_slist(list)-1);
    printf("List after removing last position: ");
    print_list_using_for(list);

    printf("\nExtending list\n");
    SList list2 = create_slist();
    for(i = 1; i < 11; i++)
    {
        value = (int*) malloc(sizeof(int));
        *value = i*10;
        append_slist(list, value);
    }
    extend_slist(list, list2);
    printf("List after extend: ");
    print_list_using_for(list);

    printf("\nSearching index of 60 in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 60;
    int index = index_of_slist(list, value, cmpfunc);
    printf("Index of 60 in list: %d\n", index);

    printf("\nSearching index of 1000 (dont exists) in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 1000;
    index = index_of_slist(list, value, cmpfunc);
    printf("Index of 1000 in list: %d\n", index);

    printf("\nContains value 60 in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 60;
    int exists = contains_slist(list, value, cmpfunc);
    printf("Exists value 60 in list: %d\n", exists);

    printf("\nContains value 1000 (dont exists) in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 1000;
    exists = contains_slist(list, value, cmpfunc);
    printf("Exists value 1000 in list: %d\n", exists);

    printf("\nList to array\n");
    void** array = to_array_slist(list);
    printf("Array: ");
    print_array(array, size_slist(list));

    printf("\nReversing list\n");
    reverse_slist(list);
    printf("List after reverse: ");
    print_list_using_for(list);

    printf("\nSorting list\n");
    sort_slist(list, cmpfunc);
    printf("List after sort: ");
    print_list_using_for(list);

    list2 = destroy_slist(list2);
    list = destroy_slist(list);
}