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
#include "./include/stack.h"

struct stack_node
{
    void* value;
    struct stack_node *next;
};
typedef struct stack_node *StackNode;

struct stack_config
{
    void (*remove_callback) (void*);
};
typedef struct stack_config *Stack_Config;

struct stack
{
    size_t size;
    StackNode first;
    Stack_Config config;
};

struct stack_iterator
{
    Stack stack;
    StackNode head;
    StackNode next;
};

Stack create_stack()
{
    Stack s = (Stack) malloc(sizeof(struct stack));
    if(!s)
        return NULL;

    Stack_Config config = malloc(sizeof(struct stack_config));
    if(!config)
    {
        free(s);
        return NULL;
    }

    s->size = 0;
    s->config = config;
    s->first = NULL;

    return s;
}

int set_stack_destruction_function_on_remove(Stack stack, void (*remove_callback) (void*))
{
    if(!stack)
        return 0;

    stack->config->remove_callback = remove_callback;
    return 1;
}

Stack destroy_stack(Stack stack)
{
    if(!stack)
        return NULL;

    while(stack->size > 0)
    {
        StackNode next_top = stack->first->next;

        if(stack->config->remove_callback)
            stack->config->remove_callback(stack->first->value);

        free(stack->first);
        stack->first = next_top;
        stack->size--;
    }

    free(stack->config);
    free(stack);
    return NULL;
}

int push_stack(Stack stack, void* value)
{
    if(!stack)
        return 0;

    StackNode node = (StackNode) malloc(sizeof(struct stack_node));
    if(!node)
        return 0;

    node->value = value;
    node->next = stack->first;
    stack->first = node;
    stack->size++;

    return 1;
}

void* peek_stack(Stack stack)
{
    if(!stack)
        return NULL;

    return stack->first->value;
}

int pop_stack(Stack stack, void** out)
{
    if(!stack)
        return 0;

    if(stack->size == 0)
        return 0;

    StackNode remove_node = stack->first;
    stack->first = stack->first->next;
    stack->size--;

    if(out)
        *out = remove_node->value;
    else if(stack->config->remove_callback)
        stack->config->remove_callback(remove_node->value);

    free(remove_node);
    return 1;
}

int size_stack(Stack stack)
{
    if(!stack)
        return -1;

    return (int) stack->size;
}

/*
 * ITERATOR
 */
Stack_Iterator create_stack_iterator(Stack stack)
{
    if(!stack)
        return NULL;

    Stack_Iterator iter = (Stack_Iterator) malloc(sizeof(struct stack_iterator));
    if(!iter)
        return NULL;

    iter->stack = stack;
    iter->head = NULL;
    iter->next = stack->first;

    return iter;
}

Stack_Iterator destroy_stack_iterator(Stack_Iterator stack_iterador)
{
    if(!stack_iterador)
        return NULL;

    free(stack_iterador);
    return NULL;
}

int stack_iterator_has_next(Stack_Iterator stack_iterador)
{
    if(!stack_iterador)
        return 0;

    if(!stack_iterador->next)
        return 0;
    else
        return 1;
}

void* stack_iterator_next(Stack_Iterator stack_iterador)
{
    if(!stack_iterador)
        return NULL;

    if(stack_iterador->next)
    {
        stack_iterador->head = stack_iterador->next;
        stack_iterador->next = stack_iterador->head->next;

        return stack_iterador->head->value;
    }

    return NULL;
}

