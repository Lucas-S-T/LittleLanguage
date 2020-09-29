//
// Created by arch on 9/29/20.
//

#include "../ll.h"


void __rjmp(vm_T *v, instruction_T *i){

    long os = i->larg0;

    v->pc+=os-1;

}