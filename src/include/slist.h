//
// Created by arthur on 15/12/18.
//

#ifndef CONTAINER_C_SLIST_H
#define CONTAINER_C_SLIST_H

typedef struct slist* SList;
typedef struct slist_iterator* SList_Iterator;

extern SList create_slist();
extern int set_destruction_function_on_remove(SList sList, void (*remove_callback) (void*));
extern SList destroy_slist(SList sList);

extern int append_slist(SList sList, void* value);
extern int prepend_slist(SList sList, void* value);
extern int insert_slist(SList sList, int index, void* value);
extern int extend_slist(SList sList_dest, SList sList_source);

extern int size_slist(SList sList);
extern int is_empty_slist(SList sList);

extern void* get_slist(SList sList, int index);
extern int set_slist(SList sList, int index, void* value, void** out);

extern int remove_index_slist(SList sList, int index, void** out);
extern int remove_value_slist(SList sList, void* value, int (*cmp)(const void*, const void*), void** out);
extern int clear_slist(SList sList);

extern int index_of_slist(SList sList, void* value, int (*cmp)(const void*, const void*));
extern int contains_slist(SList sList, void* value, int (*cmp)(const void*, const void*));

extern void** to_array_slist(SList sList);
extern int reverse_slist(SList sList);
extern int sort_slist(SList sList, int (*cmp)(const void*, const void*));
extern SList copy_shallow_slist(SList sList);

extern SList_Iterator create_slist_iterator(SList sList);
extern SList_Iterator destroy_slist_iterator(SList_Iterator sList_iterador);
extern int slist_iterator_has_next(SList_Iterator sList_iterator);
extern void* slist_iterator_next(SList_Iterator sList_iterator);
extern int slist_iterator_remove(SList_Iterator sList_iterator, void** out);

#endif //CONTAINER_C_SLIST_H
