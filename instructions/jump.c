//
// Created by arch on 9/29/20.
//

#include "../ll.h"


void __rjmp(vm_T *v, instruction_T *i){

    long os = i->larg0;

    v->pc+=os-1;

}

void __cjmp(vm_T *v, instruction_T *i){

    memory_T *m = vm_stack_pop(v->generalStack);

    int vm = vm_ctoi(m->content);

    if(vm) {
        long os = i->larg0;
        v->pc += os - 1;
    }

}