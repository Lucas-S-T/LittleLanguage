//
// Created by arch on 9/28/20.
//

#include <stdio.h>
#include <stdlib.h>
#include "../ll.h"

void __out_string(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id_or_die(v, mid);

    memory_T *m = v->memory[mi];

    for(int in = 0; in<m->size; in++){

        putchar(m->content[in]);

    }

    putchar('\n');

}

void __out_int(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id_or_die(v, mid);


    memory_T *m = v->memory[mi];

    int vl = vm_ctoi(m->content);

    printf("%i\n", vl);

}