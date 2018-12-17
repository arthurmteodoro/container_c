//
// Created by arthur on 15/12/18.
//

#include <stdlib.h>
#include "./include/utils.h"
#include "./include/slist.h"

struct node
{
    void* value;
    struct node *next;
};

typedef struct node *Node;

struct slist_config
{
    void (*remove_callback) (void*);
};
typedef struct slist_config* SList_Config;

struct slist
{
    size_t size;
    Node first;

    SList_Config configs;
};

struct slist_iterator
{
    int index;
    size_t size;
    SList list;
    Node head;
    Node next;
    Node prev;
};

SList create_slist()
{
    SList sList = (SList) malloc(sizeof(struct slist));

    if(sList == NULL)
        return NULL;

    SList_Config config = (SList_Config) malloc(sizeof(struct slist_config));

    if(config == NULL)
        return NULL;

    config->remove_callback = NULL;

    sList->size = 0;
    sList->first = NULL;
    sList->configs = config;
    return  sList;
}

int set_destruction_function_on_remove(SList sList, void (*remove_callback) (void*))
{
    if(sList == NULL)
        return 0;

    if(remove_callback == NULL)
        return 0;

    sList->configs->remove_callback = remove_callback;
    return 1;
}

SList destroy_slist(SList sList)
{
    if(sList == NULL)
        return NULL;

    if(sList->size == 0)
    {
        free(sList->configs);
        free(sList);
        return NULL;
    }

    while(sList->size > 0)
    {
        Node remove_node = sList->first;
        sList->first = remove_node->next;

        // if a config callback to remove as config, execute this callback
        if(sList->configs->remove_callback)
            sList->configs->remove_callback(remove_node->value);

        free(remove_node);
        sList->size--;
    }

    free(sList->configs);
    free(sList);
    return NULL;
}

// insert into last position of list
int append_slist(SList sList, void* value)
{
    if(sList == NULL)
        return 0;

    Node node = (Node) malloc(sizeof(struct node));
    if(node == NULL)
        return 0;

    node->value = value;
    node->next = NULL;

    if(sList->size == 0)
    {
        sList->size = 1;
        sList->first = node;

        return 1;
    }

    Node aux = sList->first;
    while(aux->next != NULL)
    {
        aux = aux->next;
    }

    aux->next = node;
    sList->size++;

    return 1;
}

int prepend_slist(SList sList, void* value)
{
    if(sList == NULL)
        return 0;

    Node node = (Node) malloc(sizeof(struct node));
    if(node == NULL)
        return 0;

    node->value = value;
    node->next = NULL;

    if(sList->size == 0)
    {
        sList->size = 1;
        sList->first = node;

        return 1;
    }

    node->next = sList->first;
    sList->first = node;
    sList->size++;

    return 1;
}

// note que a copia vai ser rasa
int extend_slist(SList sList_dest, SList sList_source)
{
    if(sList_dest == NULL || sList_source == NULL)
        return 0;

    if(sList_source->size == 0)
        return 1;

    int amount_of_values_entered = 0;
    SList_Iterator iterator = create_slist_iterator(sList_source);
    while(slist_iterator_has_next(iterator))
    {
        void* value_to_insert = slist_iterator_next(iterator);
        if(append_slist(sList_dest, value_to_insert))
            amount_of_values_entered++;
        else
            break;
    }
    destroy_slist_iterator(iterator);

    // if any error occurred, the values already entered will be removed
    if(amount_of_values_entered != sList_source->size)
    {
        while(amount_of_values_entered != 0)
        {
            remove_index_slist(sList_dest, size_slist(sList_dest)-1, NULL);
            amount_of_values_entered--;
        }
        return 0;
    }

    sList_dest->size += sList_dest->size;
    return 1;
}

int insert_slist(SList sList, int index, void* value)
{
    if(sList == NULL)
        return 0;

    if(index < 0)
        return 0;

    if(index >= sList->size)
        return append_slist(sList, value);

    if(index == 0)
        return prepend_slist(sList, value);

    Node node = (Node) malloc(sizeof(struct node));
    if(node == NULL)
        return 0;

    node->value = value;

    int counter = 0;
    Node aux = sList->first;
    while(counter < index-1)
    {
        aux = aux->next;
        counter++;
    }

    node->next = aux->next;
    aux->next = node;
    sList->size++;

    return 1;
}

int size_slist(SList sList)
{
    if(sList == NULL)
        return -1;

    return (int) sList->size;
}

int is_empty_slist(SList sList)
{
    if(sList == NULL)
        return -1;

    if(sList->size == 0)
        return 1;
    else
        return 0;
}

void* get_slist(SList sList, int index)
{
    if(sList == NULL)
        return NULL;

    if(sList->size == 0)
        return NULL;

    if(index < 0 || index >= sList->size)
        return NULL;

    if(index == 0)
        return sList->first->value;

    Node aux = sList->first;
    int counter = 0;
    while(counter != index)
    {
        aux = aux->next;
        counter++;
    }

    return aux->value;
}

int set_slist(SList sList, int index, void* value, void** out)
{
    if(sList == NULL)
        return 0;

    if(index < 0 || index >= sList->size)
        return 0;

    int counter = 0;
    Node aux = sList->first;
    while(counter != index)
    {
        aux = aux->next;
        counter++;
    }

    if(sList->configs->remove_callback)
    {
        sList->configs->remove_callback(aux->value);
    }
    else
        if(out)
            *out = aux->value;
    aux->value = value;
    return 1;
}

int remove_index_slist(SList sList, int index, void** out)
{
    if(sList == NULL)
        return 0;

    if(index < 0 || index >= sList->size)
        return 0;

    // if the list has only one element
    if(sList->size == 1)
    {
        if(sList->configs->remove_callback)
            sList->configs->remove_callback(sList->first->value);
        else
            if(out)
                *out = sList->first->value;
        free(sList->first);

        sList->first = NULL;
        sList->size = 0;

        return 1;
    }

    // if is a first element
    if(index == 0)
    {
        Node new_first = sList->first->next;

        if(sList->configs->remove_callback)
            sList->configs->remove_callback(sList->first->value);
        else
            if(out)
                *out = sList->first->value;

        free(sList->first);
        sList->first = new_first;
        sList->size--;

        return 1;
    }

    // if it is an element of the middle of the list you have to search for the previous pointer
    int counter = 0;
    Node aux = sList->first;
    while(counter < index-1)
    {
        aux = aux->next;
        counter++;
    }

    // if is a last value
    if(index+1 == sList->size)
    {
        if(sList->configs->remove_callback)
            sList->configs->remove_callback(aux->next->value);
        else
            if(out)
                *out = aux->next->value;
        free(aux->next);
        aux->next = NULL;
        sList->size--;
        return 1;
    }

    Node remove_node = aux->next;
    aux->next = remove_node->next;

    if(sList->configs->remove_callback)
        sList->configs->remove_callback(remove_node->value);
    else
        if(out)
            *out = remove_node->value;

    free(remove_node);
    sList->size--;

    return 1;
}

int remove_value_slist(SList sList, void* value, int (*cmp)(const void*, const void*), void** out)
{
    if(sList == NULL)
        return 0;

    if(value == NULL)
        return 0;

    if(cmp == NULL)
        return 0;

    if(sList->size == 0)
        return 0;

    int index = index_of_slist(sList, value, cmp);
    if(index != -1)
    {
        remove_index_slist(sList, index, out);
    }
    return 0;
}

int clear_slist(SList sList)
{
    if(sList == NULL)
        return 0;

    while(!is_empty_slist(sList))
    {
        remove_index_slist(sList, 0, NULL);
    }
    return 1;
}

int index_of_slist(SList sList, void* value, int (*cmp)(const void*, const void*))
{
    if(sList == NULL)
        return -1;

    if(value == NULL)
        return -1;

    if(cmp == NULL)
        return -1;

    int index = 0;
    Node aux = sList->first;

    while(aux != NULL && (*cmp)(aux->value, value))
    {
        index++;
        aux = aux->next;
    }

    if(index == sList->size)
        return -1;
    return index;
}

int contains_slist(SList sList, void* value, int (*cmp)(const void*, const void*))
{
    if(sList == NULL)
        return 0;

    if(value == NULL)
        return 0;

    if(cmp == NULL)
        return 0;

    int index = index_of_slist(sList, value, cmp);
    if(index == -1)
        return 0;
    return 1;
}

void** to_array_slist(SList sList)
{
    if(sList == NULL)
        return NULL;

    if(sList->size == 0)
        return NULL;

    void** array = (void**) malloc(sList->size*sizeof(void*));
    if(array == NULL)
        return NULL;

    int i;
    Node aux = sList->first;
    for(i = 0; i < size_slist(sList); i++)
    {
        array[i] = aux->value;
        aux = aux->next;
    }
    return array;
}

int reverse_slist(SList sList)
{
    if(sList == NULL)
        return 0;

    if(sList->size == 0 || sList->size == 1)
        return 0;

    Node prev = NULL;
    Node next = NULL;
    Node swap = sList->first;

    while(swap != NULL)
    {
        next = swap->next;
        swap->next = prev;
        prev = swap;
        swap = next;
    }

    sList->first = prev;
    return 1;
}

int sort_slist(SList sList, int (*cmp)(const void*, const void*))
{
    if(sList == NULL)
        return 0;

    if(cmp == NULL)
        return 0;

    if(sList->size == 0 || sList->size == 1)
        return 0;

    void** arr = to_array_slist(sList);
    if(arr == NULL)
        return 0;

    quicksort(arr, 0, (int)sList->size-1, cmp);
    free(arr);

    return 1;
}

SList copy_shallow_slist(SList sList)
{
    SList new_list = create_slist();

    SList_Iterator iterator = create_slist_iterator(sList);
    while(slist_iterator_has_next(iterator))
    {
        void* value = slist_iterator_next(iterator);
        append_slist(new_list, value);
    }

    return new_list;
}


/*
 * ITERATOR
 */

SList_Iterator create_slist_iterator(SList sList)
{
    SList_Iterator iterator = (SList_Iterator) malloc(sizeof(struct slist_iterator));
    if(iterator == NULL)
        return NULL;

    iterator->index = -1;
    iterator->size = sList->size;
    iterator->list = sList;
    iterator->head = NULL;
    iterator->next = sList->first;
    iterator->prev = NULL;

    return iterator;
}

SList_Iterator destroy_slist_iterator(SList_Iterator sList_iterador)
{
    free(sList_iterador);
    return NULL;
}

int slist_iterator_has_next(SList_Iterator sList_iterator)
{
    if(sList_iterator == NULL)
        return 0;

    if(sList_iterator->next == NULL)
        return 0;

    return 1;
}

void* slist_iterator_next(SList_Iterator sList_iterator)
{
    if(sList_iterator == NULL)
        return NULL;

    if(sList_iterator->next)
    {
        sList_iterator->prev = sList_iterator->head;
        sList_iterator->head = sList_iterator->next;
        sList_iterator->next = sList_iterator->next->next;

        void* value = sList_iterator->head->value;

        return value;
    }

    return NULL;
}

int slist_iterator_remove(SList_Iterator sList_iterator, void** out)
{
    if(sList_iterator == NULL)
        return 0;

    if(sList_iterator->head == NULL)
        return 0;

    // if removing the first position
    if(sList_iterator->head == sList_iterator->list->first)
    {
        void* v = sList_iterator->head->value;
        Node aux = sList_iterator->head;

        sList_iterator->list->first = sList_iterator->next;
        sList_iterator->list->size--;

        sList_iterator->prev = NULL;
        sList_iterator->head = NULL;

        if(sList_iterator->list->configs->remove_callback)
            sList_iterator->list->configs->remove_callback(v);
        else if(out)
            *out = v;
        free(aux);

        return 1;
    }

    // if removing the last position
    if(sList_iterator->next == NULL)
    {
        void* v = sList_iterator->head->value;
        Node aux = sList_iterator->head;

        sList_iterator->prev->next = NULL;
        sList_iterator->head = sList_iterator->prev;

        sList_iterator->list->size--;

        if(sList_iterator->list->configs->remove_callback)
            sList_iterator->list->configs->remove_callback(v);
        else if(out)
            *out = v;
        free(aux);

        return 1;
    }

    // is a middle element
    void* v = sList_iterator->head->value;
    Node aux = sList_iterator->head;

    sList_iterator->prev->next = sList_iterator->next;
    sList_iterator->list->size--;
    sList_iterator->head = sList_iterator->prev;

    if(sList_iterator->list->configs->remove_callback)
        sList_iterator->list->configs->remove_callback(v);
    else if(out)
        *out = v;
    free(aux);

    return 1;
}

