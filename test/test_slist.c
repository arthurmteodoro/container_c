/*
 * MIT License
 *
 * Copyright (c) 2018 Arthur Alexsander Martins Teodoro
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

void destroy_func(void* value)
{
    free(value);
}

int main() {
    int i;
    SList list = create_slist();
    set_slist_destruction_function_on_remove(list, destroy_func);

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
    set_slist(list, 6, value, NULL);
    printf("List after set: ");
    print_list_using_for(list);

    printf("\nRemoving position 4 of the list\n");
    remove_index_slist(list, 4, NULL);
    printf("List after removing position 4: ");
    print_list_using_for(list);

    printf("\nRemoving position 0 of the list\n");
    remove_index_slist(list, 0, NULL);
    printf("List after removing position 0: ");
    print_list_using_for(list);

    printf("\nRemoving the last element of the list\n");
    remove_index_slist(list, size_slist(list)-1, NULL);
    printf("List after removing last position: ");
    print_list_using_for(list);

    printf("\nRemoving value 6 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 6;
    remove_value_slist(list, value, cmpfunc, NULL);
    printf("List after removing value 6: ");
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

    printf("\nPrint using iterator\n");
    SList_Iterator iterator = create_slist_iterator(list);
    while(slist_iterator_has_next(iterator))
    {
        value = (int*) slist_iterator_next(iterator);
        printf("%d ", *value);
    }
    destroy_slist_iterator(iterator);
    printf("\n");

    printf("\nRemoving first element using iterator\n");
    iterator = create_slist_iterator(list);
    index = 0;
    while(slist_iterator_has_next(iterator))
    {
        value = (int*) slist_iterator_next(iterator);
        printf("%d ", *value);
        if(index == 0)
            slist_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_slist_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    printf("\nRemoving first element using iterator as list only one element\n");
    SList list3 = create_slist();
    value = malloc(sizeof(int));
    *value = 400;
    append_slist(list3, value);

    iterator = create_slist_iterator(list3);
    index = 0;
    while(slist_iterator_has_next(iterator))
    {
        value = (int*) slist_iterator_next(iterator);
        printf("%d ", *value);
        if(index == 0)
            slist_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_slist_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list3);
    printf("\nSize of list3: %d", size_slist(list3));

    printf("\n\nRemoving last element using iterator\n");
    iterator = create_slist_iterator(list);
    index = 0;
    while(slist_iterator_has_next(iterator))
    {
        value = (int*) slist_iterator_next(iterator);
        printf("%d ", *value);
        if(index == size_slist(list)-1)
            slist_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_slist_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    printf("\nRemoving even numbers using iterator\n");
    iterator = create_slist_iterator(list);
    while(slist_iterator_has_next(iterator))
    {
        value = (int*) slist_iterator_next(iterator);
        printf("%d ", *value);
        if(*value % 2 == 0)
            slist_iterator_remove(iterator, NULL);
    }
    destroy_slist_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    list3 = destroy_slist(list3);
    list2 = destroy_slist(list2);
    list = destroy_slist(list);
}