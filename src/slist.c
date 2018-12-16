//
// Created by arthur on 15/12/18.
//

#include <stdlib.h>
#include "./include/slist.h"

struct node
{
    void* value;
    struct node *next;
};

typedef struct node *Node;

struct slist
{
    size_t size;
    Node first;
};

struct slist_iterator
{
    int index;
    size_t size;
    SList list;
    Node head;
    Node next;
};

SList create_slist()
{
    SList sList = (SList) malloc(sizeof(struct slist));

    if(sList == NULL)
        return NULL;

    sList->size = 0;
    sList->first = NULL;
    return  sList;
}

SList destroy_slist(SList sList)
{
    if(sList == NULL)
        return NULL;

    if(sList->size == 0)
    {
        free(sList);
        return NULL;
    }

    while(sList->size > 0)
    {
        Node remove_node = sList->first;
        sList->first = remove_node->next;
        free(remove_node->value);
        free(remove_node);
        sList->size--;
    }

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

int set_slist(SList sList, int index, void* value)
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

    free(aux->value);
    aux->value = value;
    return 1;
}

int remove_index_slist(SList sList, int index)
{
    if(sList == NULL)
        return 0;

    if(index < 0 || index >= sList->size)
        return 0;

    // if the list has only one element
    if(sList->size == 1)
    {
        free(sList->first->value);
        free(sList->first);

        sList->first = NULL;
        sList->size = 0;

        return 1;
    }

    // if is a first element
    if(index == 0)
    {
        Node new_first = sList->first->next;
        free(sList->first->value);
        free(sList->first);
        sList->first = new_first;
        sList->size--;
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
        free(aux->next->value);
        free(aux->next);
        aux->next = NULL;
        sList->size--;
        return 1;
    }

    Node remove_node = aux->next;
    aux->next = remove_node->next;
    free(remove_node->value);
    free(remove_node);
    sList->size--;

    return 1;
}



/*
 * ITERATOR
 */

SList_Iterator create_slist_iterator(SList sList)
{
    SList_Iterator iterator = (SList_Iterator) malloc(sizeof(struct slist_iterator));
    if(iterator == NULL)
        return NULL;

    iterator->index = 0;
    iterator->size = sList->size;
    iterator->list = sList;
    iterator->head = sList->first;
    iterator->next = sList->first->next;
}

int slist_iterator_has_next(SList_Iterator sList_iterator)
{
    if(sList_iterator->head == NULL)
        return 0;

    return 1;
}

void* slist_iterator_next(SList_Iterator sList_iterator)
{
    void* value = sList_iterator->head->value;
    sList_iterator->index++;
    sList_iterator->head = sList_iterator->next;

    if(sList_iterator->next != NULL)
        sList_iterator->next = sList_iterator->next->next;

    return value;
}

