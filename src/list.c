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
#include <stdio.h>
#include "./include/utils.h"
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

struct list_iterator
{
    List list;
    ListNode head;
    ListNode next;
    ListNode prev;
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
    if(!list_dest || !list_source)
        return 0;

    if(list_source->size == 0)
        return 1;

    int amount_of_values_entered = 0;
    List_Iterator iterator = create_list_iterator(list_source);
    while(list_iterator_has_next(iterator))
    {
        void* value_to_insert = list_iterator_next(iterator);
        if(append_list(list_dest, value_to_insert))
            amount_of_values_entered++;
        else
            break;
    }
    destroy_list_iterator(iterator);

    // if any error occurred, the values already entered will be removed
    if(amount_of_values_entered != list_source->size)
    {
        while(amount_of_values_entered != 0)
        {
            remove_index_list(list_dest, size_list(list_dest)-1, NULL);
            amount_of_values_entered--;
        }
        return 0;
    }

    list_dest->size += list_dest->size;
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

    if(list->size == 0)
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
    list->size--;

    return 1;
}

int remove_value_list(List list, void* value, int (*cmp)(const void*, const void*), void** out)
{
    if(!list)
        return 0;

    if(!value)
        return 0;

    if(!cmp)
        return 0;

    if(list->size == 0)
        return 0;

    int index = index_of_list(list, value, cmp);
    if(index != -1)
        remove_index_list(list, index, out);

    return 0;
}

int clear_list(List list)
{
    if(!list)
        return 0;

    while(list->size > 0)
        remove_index_list(list, 0, NULL);

    return 1;
}

extern int index_of_list(List list, void* value, int (*cmp)(const void*, const void*))
{
    if(!list)
        return -1;

    if(!value)
        return -1;

    if(!cmp)
        return -1;

    int index = 0;
    ListNode aux = list->first;

    while(aux != NULL && (*cmp)(aux->value, value))
    {
        index++;
        aux = aux->next;
    }

    if(index == list->size)
        return -1;

    return index;
}

extern int contains_list(List list, void* value, int (*cmp)(const void*, const void*))
{
    if(!list)
        return 0;

    if(!value)
        return 0;

    if(!cmp)
        return 0;

    int index = index_of_list(list, value, cmp);

    if(index == -1)
        return 0;
    return 1;
}

void** to_array_list(List list)
{
    if(!list)
        return NULL;

    if(list->size == 0)
        return NULL;

    void** arr = (void**) malloc(list->size * sizeof(void*));
    if(!arr)
        return NULL;

    int i;
    ListNode aux = list->first;
    for(i = 0; i < size_list(list); i++)
    {
        arr[i] = aux->value;
        aux = aux->next;
    }
    return arr;
}

int reverse_list(List list)
{
    if(!list)
        return 0;

    if(list->size <= 1)
        return 0;

    ListNode left = list->first;
    ListNode right = list->last;

    int i;
    for(i = 0; i < list->size/2; i++)
    {
        void* aux = left->value;
        left->value = right->value;
        right->value = aux;

        left = left->next;
        right = right->prev;
    }

    return 1;
}

int sort_list(List list, int (*cmp)(const void*, const void*))
{
    if(!list)
        return 0;

    if(!cmp)
        return 0;

    if(list->size <= 1)
        return 0;

    void** arr = to_array_list(list);
    if(!arr)
        return 0;

    quicksort(arr, 0, (int)list->size-1, cmp);
    free(arr);

    return 1;
}

List copy_shallow_slist(List list)
{
    List new_list = create_list();

    List_Iterator iterator = create_list_iterator(list);
    while(list_iterator_has_next(iterator))
    {
        void* value = list_iterator_next(iterator);
        append_list(new_list, value);
    }
    destroy_list_iterator(iterator);

    return new_list;
}

/*
 * ITERATOR
 */

List_Iterator create_list_iterator(List list)
{
    List_Iterator iterator = (List_Iterator) malloc(sizeof(struct list_iterator));
    if(!iterator)
        return NULL;

    iterator->list = list;
    iterator->head = NULL;
    iterator->next = list->first;
    iterator->prev = NULL;

    return iterator;
}

List_Iterator destroy_list_iterator(List_Iterator list_iterador)
{
    free(list_iterador);
    return NULL;
}

int list_iterator_has_next(List_Iterator list_iterator)
{
    if(!list_iterator)
        return 0;

    if(!list_iterator->next)
        return 0;

    return 1;
}

void* list_iterator_next(List_Iterator list_iterator)
{
    if(!list_iterator)
        return NULL;

    if(list_iterator->next)
    {
        list_iterator->prev = list_iterator->head;
        list_iterator->head = list_iterator->next;
        list_iterator->next = list_iterator->next->next;

        void* value = list_iterator->head->value;
        return value;
    }

    return NULL;
}

extern int list_iterator_remove(List_Iterator list_iterator, void** out)
{
    if(!list_iterator)
        return 0;

    if(!list_iterator->head)
        return 0;

    // if removing the first position
    if(list_iterator->head == list_iterator->list->first)
    {
        void* v = list_iterator->head->value;
        ListNode aux = list_iterator->head;

        list_iterator->list->first = list_iterator->next;
        if(list_iterator->list->first)
            list_iterator->list->first->prev = NULL;
        list_iterator->list->size--;

        list_iterator->prev = NULL;
        list_iterator->head = NULL;

        if(list_iterator->list->config->remove_callback)
            list_iterator->list->config->remove_callback(v);
        else if(out)
            *out = v;
        free(aux);

        return 1;
    }

    // if removing the last position
    if(list_iterator->next == NULL)
    {
        remove_index_list(list_iterator->list, size_list(list_iterator->list)-1, out);

        return 1;
    }

    // is a middle element
    void* v = list_iterator->head->value;
    ListNode aux = list_iterator->head;

    list_iterator->prev->next = list_iterator->next;
    list_iterator->next->prev = list_iterator->prev;
    list_iterator->list->size--;
    list_iterator->head = list_iterator->prev;

    if(list_iterator->list->config->remove_callback)
        list_iterator->list->config->remove_callback(v);
    else if(out)
        *out = v;
    free(aux);

    return 1;
}
