//
// Created by arch on 9/28/20.
//

#include "../ll.h"

void __call(vm_T *v, instruction_T *i){

    long nis = vm_instruction_set_get_by_func_id_or_die(v, i->carg0);

    vm_stack_push(v->isStack, v->current_function);
    vm_stack_push(v->pcStack, (void*)v->pc);


    v->current_function = v->instruction_set[nis];
    v->pc = 0;


}

void __ret(vm_T *v, instruction_T *i){

    v->current_function = vm_stack_pop(v->isStack);
    v->pc = (ulong) vm_stack_pop(v->pcStack);


}