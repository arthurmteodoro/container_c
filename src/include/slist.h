//
// Created by arthur on 15/12/18.
//

#ifndef CONTAINER_C_SLIST_H
#define CONTAINER_C_SLIST_H

typedef struct slist* SList;
typedef struct slist_iterator* SList_Iterator;

extern SList create_slist();
extern SList destroy_slist(SList sList);
extern int append_slist(SList sList, void* value);
extern int prepend_slist(SList sList, void* value);
extern int insert_slist(SList sList, int index, void* value);
extern int size_slist(SList sList);
extern void* get_slist(SList sList, int index);
extern int set_slist(SList sList, int index, void* value);
extern int remove_index_slist(SList sList, int index);

extern SList_Iterator create_slist_iterator(SList sList);
extern int slist_iterator_has_next(SList_Iterator sList_iterator);
extern void* slist_iterator_next(SList_Iterator sList_iterator);

#endif //CONTAINER_C_SLIST_H
