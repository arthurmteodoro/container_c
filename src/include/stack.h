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

#ifndef CONTAINER_C_STACK_H
#define CONTAINER_C_STACK_H

typedef struct stack *Stack;
typedef struct stack_iterator *Stack_Iterator;

extern Stack create_stack();
extern int set_stack_destruction_function_on_remove(Stack stack, void (*remove_callback) (void*));
extern Stack destroy_stack(Stack stack);

extern int push_stack(Stack stack, void* value);
extern void* peek_stack(Stack stack);
extern int pop_stack(Stack stack, void** out);

extern int size_stack(Stack stack);

extern Stack_Iterator create_stack_iterator(Stack stack);
extern Stack_Iterator destroy_stack_iterator(Stack_Iterator stack_iterador);
extern int stack_iterator_has_next(Stack_Iterator stack_iterador);
extern void* stack_iterator_next(Stack_Iterator stack_iterador);

#endif //CONTAINER_C_STACK_H
