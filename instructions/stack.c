//
// Created by arch on 9/28/20.
//

#include <memory.h>
#include <stdlib.h>
#include "../ll.h"

void __push(vm_T *v, instruction_T *i){

    ulong mid = vm_memory_find_index_by_id_or_die(v, i->carg0);

    memory_T *m = v->memory[mid];

    memory_T *cp = malloc(sizeof(struct MEMORY_STRUCT)+m->size);
    memcpy(cp, m, sizeof(struct MEMORY_STRUCT)+m->size);

    vm_stack_push(v->generalStack, cp);

}


void __pop(vm_T *v, instruction_T *i){

    memory_T *m = vm_stack_pop(v->generalStack);

    memory_T *al = vm_memory_allocate_or_die(v, i->carg0, m->size);
    memcpy(al, m, sizeof(struct MEMORY_STRUCT)+m->size);
    al->id = i->carg0;
    free(m);


}