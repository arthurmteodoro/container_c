//
// Created by arthur on 15/12/18.
//

#ifndef CONTAINER_C_SLIST_H
#define CONTAINER_C_SLIST_H

typedef struct slist * SList;

extern SList create_slist();
extern SList destroy_slist(SList sList);
extern int append_slist(SList sList, void* value);
extern int insert_slist(SList sList, void* value, int index);

#endif //CONTAINER_C_SLIST_H
