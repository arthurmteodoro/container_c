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

void destroy_func(void* value)
{
    free(value);
}

int main()
{
    List list = create_list();
    set_list_destruction_function_on_remove(list, destroy_func);

    printf("Inserting 10 elements in the list using append\n");
    int i;
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

    list = destroy_list(list);
}