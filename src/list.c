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

List destroy_list(List list)
{
    if(list == NULL)
        return NULL;

    if(list->size == 0)
    {
        free(list->config);
        free(list);
        return NULL;
    }

    while(list->size > 1)
    {
        ListNode node = list->last;
        if(!list->last)
            list->last = list->first;
        else
            list->last = list->last->prev;

        if(list->config->remove_callback)
            list->config->remove_callback(node->value);

        list->size--;
        free(node);
    }

    free(list->config);
    free(list);
    return NULL;
}

int append_list(List list, void* value)
{
    if(list == NULL)
        return 0;

    ListNode node = (ListNode) malloc(sizeof(struct list));
    if(node == NULL)
        return 0;

    node->value = value;

    if(list->size == 0)
    {
        node->prev = NULL;
        node->next = NULL;

        list->first = node;
        list->last = node;
        list->size = 1;

        return 1;
    }

    list->last->next = node;
    node->prev = list->last;
    node->next = NULL;
    list->last = node;
    list->size++;

    return 1;
}

int prepend_list(List list, void* value)
{
    if(!list)
        return 0;

    ListNode node = (ListNode) malloc(sizeof(struct list));
    if(!node)
        return 0;

    node->value = value;

    if(list->size == 0)
    {
        node->prev = NULL;
        node->next = NULL;

        list->first = node;
        list->last = node;
        list->size = 1;

        return 1;
    }

    node->next = list->first;
    node->prev = NULL;
    list->first->prev = node;
    list->first = node;
    list->size++;

    return 1;
}

int insert_list(List list, int index, void* value)
{
    if(!list)
        return 0;

    if(index < 0)
        return 0;

    if(index >= list->size)
        return append_list(list, value);

    if(index == 0)
        return prepend_list(list, value);

    ListNode node = (ListNode) malloc(sizeof(struct list_node));
    if(!node)
        return 0;

    node->value = value;

    if(index <= list->size/2)
    {
        int counter = 0;
        ListNode aux = list->first;
        while(counter < index-1)
        {
            aux = aux->next;
            counter++;
        }

        node->next = aux->next;
        aux->next->prev = node;
        aux->next = node;
        node->prev = aux;
        list->size++;

        return 1;
    }
    else
    {
        int counter = (int) list->size;
        ListNode aux = list->last;
        while(counter > index)
        {
            aux = aux->prev;
            counter--;
        }

        node->next = aux->next;
        aux->next->prev = node;
        aux->next = node;
        node->prev = aux;
        list->size++;

        return 1;
    }
}

int extend_list(List list_dest, List list_source)
{
    // TODO: implementar esta funcao
    return 1;
}

int size_list(List list)
{
    if(!list)
        return -1;

    return (int) list->size;
}

extern int is_empty_list(List list)
{
    if(!list)
        return -1;

    if(list->size == 0)
        return 1;
    else
        return 0;
}

extern void* get_list(List list, int index)
{
    if(!list)
        return NULL;

    if(list->size == 0)
        return NULL;

    if(index < 0 || index >= list->size)
        return NULL;

    if(index == 0)
        return list->first->value;

    if(index <= list->size/2)
    {
        ListNode aux = list->first;
        int counter = 0;
        while(counter != index)
        {
            aux = aux->next;
            counter++;
        }

        return aux->value;
    }
    else
    {
        ListNode aux = list->last;
        int counter = (int) list->size-1;
        while(counter != index)
        {
            aux = aux->prev;
            counter--;
        }

        return aux->value;
    }
}

int set_list(List list, int index, void* value, void** out)
{
    if(!list)
        return 0;

    if(index < 0 || index >= list->size)
        return 0;

    ListNode aux = NULL;
    int counter = 0;
    if(index <= list->size/2)
    {
        counter = 0;
        aux = list->first;
        while(counter != index)
        {
            aux = aux->next;
            counter++;
        }
    }
    else
    {
        counter = (int) list->size-1;
        aux = list->last;
        while(counter != index)
        {
            aux = aux->prev;
            counter--;
        }
    }

    if(list->config->remove_callback)
        list->config->remove_callback(aux->value);
    else if(out)
        *out = aux->value;

    aux->value = value;
    return 1;
}

int remove_index_list(List list, int index, void** out)
{
    if(!list)
        return 0;

    if(index < 0 || index >= list->size)
        return 0;

    if(list->size == 1)
    {
        if(list->config->remove_callback)
            list->config->remove_callback(list->first->value);
        else if(out)
            *out = list->first->value;
        free(list->first);

        list->first = NULL;
        list->last = NULL;
        list->size = 0;

        return 1;
    }

    if(index == 0)
    {
        ListNode new_first = list->first->next;

        if(list->config->remove_callback)
            list->config->remove_callback(list->first->value);
        else if(out)
            *out = list->first->value;

        free(list->first);
        new_first->prev = NULL;
        list->first = new_first;
        list->size--;

        return 1;
    }

    if(index == list->size-1)
    {
        ListNode new_last = list->last->prev;

        if(list->config->remove_callback)
            list->config->remove_callback(list->last->value);
        else if(out)
            *out = list->last->value;

        free(list->last);
        new_last->next = NULL;
        list->last = new_last;
        list->size--;

        return 1;
    }

    ListNode aux = NULL;
    int counter = 0;
    if(index <= list->size/2)
    {
        counter = 0;
        aux = list->first;
        while(counter != index)
        {
            aux = aux->next;
            counter++;
        }
    }
    else
    {
        counter = (int) list->size-1;
        aux = list->last;
        while(counter != index)
        {
            aux = aux->prev;
            counter--;
        }
    }

    ListNode node_prev = aux->prev;
    ListNode node_next = aux->next;

    if(list->config->remove_callback)
        list->config->remove_callback(aux->value);
    else if(out)
        *out = aux->value;

    free(aux);
    node_prev->next = node_next;
    node_next->prev = node_prev;

    return 1;
}
