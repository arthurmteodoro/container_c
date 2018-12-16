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

    list = destroy_slist(list);
}