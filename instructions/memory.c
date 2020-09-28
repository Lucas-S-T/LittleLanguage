//
// Created by arch on 9/28/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../ll.h"


void __allocate(vm_T *v, instruction_T *i){

    ulong sz = i->larg0;
    char *id = i->carg0;

    vm_memory_allocate_or_die(v, id, sz);

}

void __free(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id_or_die(v, mid);


    vm_memory_free(v, mi);

}

void __allocate_int(vm_T *v, instruction_T *i){

    char *id = i->carg0;

    vm_memory_allocate_or_die(v, id, 4);

}

int vm_ctoi(char *c){

    union {

        int i;
        char c[4];

    }t;

    t.c[0] = c[0];
    t.c[1] = c[1];
    t.c[2] = c[2];
    t.c[3] = c[3];

    return t.i;

}


void vm_itoc(int i, char *c){

    union {

        int i;
        char c[4];

    }t;

    t.i = i;

    c[0] = t.c[0];
    c[1] = t.c[1];
    c[2] = t.c[2];
    c[3] = t.c[3];

}