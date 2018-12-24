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

#include <stdio.h>
#include <stdlib.h>
#include "../src/include/stack.h"

void print_stack(Stack stack)
{
    printf("__   __\n");
    Stack_Iterator iter = create_stack_iterator(stack);
    while(stack_iterator_has_next(iter))
    {
        int* value = (int*) stack_iterator_next(iter);
        printf(" | %d |\n", *value);
    }
    printf(" -----\n");
    destroy_stack_iterator(iter);
}

void destroy_func(void* value)
{
    free(value);
}


int main()
{
    Stack stack = create_stack();
    set_stack_destruction_function_on_remove(stack, destroy_func);
    int i;

    printf("Inserting 10 elements in the stack\n");
    for(i = 0; i < 10; i++)
    {
        int* value = (int*) malloc(sizeof(int));
        *value = i;
        push_stack(stack, value);
    }
    printf("Stack after insertion:\n");
    print_stack(stack);

    printf("\nPeeking value of stack\n");
    int* value = peek_stack(stack);
    printf("Value of top: %d\n", *value);

    printf("\nRemoving value of stack:\n");
    pop_stack(stack, NULL);
    printf("Stack after remove:\n");
    print_stack(stack);

    printf("\nRemoving value of stack but getting value:\n");
    pop_stack(stack, (void**)&value);
    printf("Value that left the stack: %d\n", *value);
    printf("Stack after remove:\n");
    print_stack(stack);

    stack = destroy_stack(stack);
    return 0;
}

