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

#ifndef CONTAINER_C_LIST_H
#define CONTAINER_C_LIST_H

typedef struct list *List;

extern List create_list();
extern int set_list_destruction_function_on_remove(List list, void (*remove_callback) (void*));
extern List destroy_list(List list);

extern int append_list(List list, void* value);
extern int prepend_list(List list, void* value);
extern int insert_list(List list, int index, void* value);
extern int extend_list(List list_dest, List list_source);

extern int size_list(List list);
extern int is_empty_list(List list);

extern void* get_list(List list, int index);
extern int set_list(List list, int index, void* value, void** out);

extern int remove_index_list(List list, int index, void** out);

#endif //CONTAINER_C_LIST_H
