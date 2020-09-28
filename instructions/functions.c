//
// Created by arch on 9/28/20.
//

#include <stdlib.h>
#include "../ll.h"

void __call(vm_T *v, instruction_T *i){

    long nis = vm_instruction_set_get_by_func_id_or_die(v, i->carg0);

    vm_stack_push(v->isStack, v->current_function);
    vm_stack_push(v->pcStack, (void*)v->pc);
    vm_stack_push(v->fidStack, (void*)v->current_function_id);

    v->current_function = v->instruction_set[nis];
    v->pc = 0;
    v->current_function_id = random();


}

void __ret(vm_T *v, instruction_T *i){


    vm_memory_free_current_fid(v);

    v->current_function = vm_stack_pop(v->isStack);
    v->pc = (ulong) vm_stack_pop(v->pcStack);
    v->current_function_id = (ulong) vm_stack_pop(v->fidStack);



}