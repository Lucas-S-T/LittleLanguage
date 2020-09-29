//
// Created by arch on 9/28/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "../ll.h"

void __dump_string(vm_T *v, instruction_T *i){

    char *mid = i->carg0;
    char *cont = i->carg1;

    ulong mi = vm_memory_find_index_by_id_or_die(v, mid);

    memory_T *m = v->memory[mi];

    for(int j = 0; j<strlen(cont); j++){
        m->content[j] = cont[j];
    }


}



void __load_int_const(vm_T *v, instruction_T *i){

    ulong cont = i->larg0;
    char *id = i->carg0;

    ulong mi = vm_memory_find_index_by_id_or_die(v, id);


    memory_T *m = v->memory[mi];


    vm_itoc(cont, m->content);

}

void __size(vm_T *v, instruction_T *i){


    char *id = i->carg0;

    ulong mi = vm_memory_find_index_by_id_or_die(v, id);

    memory_T *m = v->memory[mi];

    memory_T *mv = malloc(sizeof(struct MEMORY_STRUCT)+4);
    mv->size = 4;
    mv->used = 1;
    vm_itoc(m->size, mv->content);


    vm_stack_push(v->generalStack, mv);

}