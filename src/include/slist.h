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

#ifndef CONTAINER_C_SLIST_H
#define CONTAINER_C_SLIST_H

typedef struct slist* SList;
typedef struct slist_iterator* SList_Iterator;

extern SList create_slist();
extern int set_slist_destruction_function_on_remove(SList sList, void (*remove_callback) (void*));
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
