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
    Node last;
};

SList create_slist()
{
    SList sList = (SList) malloc(sizeof(struct slist));

    if(sList == NULL)
        return NULL;

    sList->size = 0;
    sList->first = NULL;
    sList->last = NULL;
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
        return 1;

    Node node = (Node) malloc(sizeof(struct node));
    if(node == NULL)
        return 1;

    node->value = value;
    node->next = NULL;

    if(sList->size == 0)
    {
        sList->size = 1;
        sList->last = node;
        sList->first = node;

        return 0;
    }

    sList->last->next = node;
    sList->last = node;
    sList->size++;

    return 0;
}

int insert_slist(SList sList, void* value, int index)
{
    if(sList == NULL)
        return 1;

    if
}

