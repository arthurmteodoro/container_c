//
// Created by arthur on 15/12/18.
//

#include <stdio.h>
#include <stdlib.h>
#include "../src/include/slist.h"

int main() {
    int i;
    SList list = create_slist();
    for(i = 0; i < 10; i++)
    {
        int* value = (int*) malloc(sizeof(int));
        *value = i;
        append_slist(list, value);
    }

    list = destroy_slist(list);
}