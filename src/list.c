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

#include <stdlib.h>
#include "./include/list.h"

struct list_node
{
    void* value;
    struct list_node* next;
    struct list_node* prev;
};
typedef struct list_node *ListNode;

struct list_config
{
    void (*remove_callback) (void*);
};
typedef struct list_config* List_Config;

struct list
{
    size_t size;
    ListNode first;
    ListNode last;

    List_Config config;
};

List create_list()
{
    List list = (List) malloc(sizeof(struct list));
    if(list == NULL)
        return NULL;

    List_Config config = (List_Config) malloc(sizeof(struct list_config));
    if(config == NULL)
    {
        free(list);
        return NULL;
    }

    config->remove_callback = NULL;
    list->config = config;
    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

int set_list_destruction_function_on_remove(List list, void (*remove_callback) (void*))
{
    if(list == NULL)
        return 0;
    if(remove_callback == NULL)
        return 0;

    list->config->remove_callback = remove_callback;
    return 1;
}
