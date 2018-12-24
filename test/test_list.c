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
#include "../src/include/list.h"

void print_list_using_for(List list)
{
    int i;
    int list_size = size_list(list);
    printf("[");
    for(i = 0; i < list_size; i++)
    {
        int* value_read = (int*) get_list(list, i);
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

int main()
{
    int i;
    List list = create_list();
    set_list_destruction_function_on_remove(list, destroy_func);

    printf("Inserting 10 elements in the list using append\n");
    for(i = 0; i < 10; i++)
    {
        int* value = (int*) malloc(sizeof(int));
        *value = i;
        append_list(list, value);
    }
    printf("List after insertion: ");
    print_list_using_for(list);

    printf("\nPrepending value 1000 in the list\n");
    int* value = (int*) malloc(sizeof(int));
    *value = 1000;
    prepend_list(list, value);
    printf("List after prepend: ");
    print_list_using_for(list);

    printf("\nInserting value 5000 in position 3 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 5000;
    insert_list(list, 3, value);
    printf("List after insert: ");
    print_list_using_for(list);

    printf("\nInserting value 767 in final position (using list size) of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 767;
    insert_list(list, size_list(list), value);
    printf("List after insert: ");
    print_list_using_for(list);

    printf("\nSetting value 323 in position 6 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 323;
    set_list(list, 6, value, NULL);
    printf("List after set: ");
    print_list_using_for(list);

    printf("\nRemoving position 4 of the list\n");
    remove_index_list(list, 4, NULL);
    printf("List after removing position 4: ");
    print_list_using_for(list);

    printf("\nRemoving position 0 of the list\n");
    remove_index_list(list, 0, NULL);
    printf("List after removing position 0: ");
    print_list_using_for(list);

    printf("\nRemoving the last element of the list\n");
    remove_index_list(list, size_list(list)-1, NULL);
    printf("List after removing last position: ");
    print_list_using_for(list);

    printf("\nRemoving value 6 of the list\n");
    value = (int*) malloc(sizeof(int));
    *value = 6;
    remove_value_list(list, value, cmpfunc, NULL);
    printf("List after removing value 6: ");
    print_list_using_for(list);

    printf("\nExtending list\n");
    List list2 = create_list();
    for(i = 1; i < 11; i++)
    {
        value = (int*) malloc(sizeof(int));
        *value = i*10;
        append_list(list, value);
    }
    extend_list(list, list2);
    printf("List after extend: ");
    print_list_using_for(list);

    printf("\nSearching index of 60 in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 60;
    int index = index_of_list(list, value, cmpfunc);
    printf("Index of 60 in list: %d\n", index);

    printf("\nSearching index of 1000 (dont exists) in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 1000;
    index = index_of_list(list, value, cmpfunc);
    printf("Index of 1000 in list: %d\n", index);

    printf("\nContains value 60 in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 60;
    int exists = contains_list(list, value, cmpfunc);
    printf("Exists value 60 in list: %d\n", exists);

    printf("\nContains value 1000 (dont exists) in list\n");
    value = (int*) malloc(sizeof(int));
    *value = 1000;
    exists = contains_list(list, value, cmpfunc);
    printf("Exists value 1000 in list: %d\n", exists);

    printf("\nList to array\n");
    void** array = to_array_list(list);
    printf("Array: ");
    print_array(array, size_list(list));

    printf("\nReversing list\n");
    reverse_list(list);
    printf("List after reverse: ");
    print_list_using_for(list);

    printf("\nSorting list\n");
    sort_list(list, cmpfunc);
    printf("List after sort: ");
    print_list_using_for(list);

    printf("\nPrint using iterator\n");
    List_Iterator iterator = create_list_iterator(list);
    while(list_iterator_has_next(iterator))
    {
        value = (int*) list_iterator_next(iterator);
        printf("%d ", *value);
    }
    destroy_list_iterator(iterator);
    printf("\n");

    printf("\nRemoving first element using iterator\n");
    iterator = create_list_iterator(list);
    index = 0;
    while(list_iterator_has_next(iterator))
    {
        value = (int*) list_iterator_next(iterator);
        printf("%d ", *value);
        if(index == 0)
            list_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_list_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    printf("\nRemoving first element using iterator as list only one element\n");
    List list3 = create_list();
    value = malloc(sizeof(int));
    *value = 400;
    append_list(list3, value);

    iterator = create_list_iterator(list3);
    index = 0;
    while(list_iterator_has_next(iterator))
    {
        value = (int*) list_iterator_next(iterator);
        printf("%d ", *value);
        if(index == 0)
            list_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_list_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list3);
    printf("\nSize of list3: %d", size_list(list3));

    printf("\n\nRemoving last element using iterator\n");
    iterator = create_list_iterator(list);
    index = 0;
    while(list_iterator_has_next(iterator))
    {
        value = (int*) list_iterator_next(iterator);
        printf("%d ", *value);
        if(index == size_list(list)-1)
            list_iterator_remove(iterator, NULL);
        index++;
    }
    destroy_list_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    printf("\nRemoving even numbers using iterator\n");
    iterator = create_list_iterator(list);
    while(list_iterator_has_next(iterator))
    {
        value = (int*) list_iterator_next(iterator);
        printf("%d ", *value);
        if(*value % 2 == 0)
            list_iterator_remove(iterator, NULL);
    }
    destroy_list_iterator(iterator);
    printf("\n");
    printf("List after remove: ");
    print_list_using_for(list);

    list3 = destroy_list(list3);
    list2 = destroy_list(list2);
    list = destroy_list(list);
}