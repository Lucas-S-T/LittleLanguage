//
// Created by arch on 9/29/20.
//

#include "../ll.h"

void __iadd(vm_T *v, instruction_T *i){

    char *a = i->carg0;
    char *b = i->carg1;

    memory_T *ma = v->memory[vm_memory_find_index_by_id_or_die(v, a)];
    memory_T *mb = v->memory[vm_memory_find_index_by_id_or_die(v, b)];

    int ia = vm_ctoi(ma->content);
    int ib = vm_ctoi(mb->content);

    vm_itoc(ia+ib, ma->content);


}

void __isub(vm_T *v, instruction_T *i){

    char *a = i->carg0;
    char *b = i->carg1;

    memory_T *ma = v->memory[vm_memory_find_index_by_id_or_die(v, a)];
    memory_T *mb = v->memory[vm_memory_find_index_by_id_or_die(v, b)];

    int ia = vm_ctoi(ma->content);
    int ib = vm_ctoi(mb->content);

    vm_itoc(ia-ib, ma->content);


}


void __imul(vm_T *v, instruction_T *i){

    char *a = i->carg0;
    char *b = i->carg1;

    memory_T *ma = v->memory[vm_memory_find_index_by_id_or_die(v, a)];
    memory_T *mb = v->memory[vm_memory_find_index_by_id_or_die(v, b)];

    int ia = vm_ctoi(ma->content);
    int ib = vm_ctoi(mb->content);

    vm_itoc(ia*ib, ma->content);


}

void __idiv(vm_T *v, instruction_T *i){

    char *a = i->carg0;
    char *b = i->carg1;

    memory_T *ma = v->memory[vm_memory_find_index_by_id_or_die(v, a)];
    memory_T *mb = v->memory[vm_memory_find_index_by_id_or_die(v, b)];

    int ia = vm_ctoi(ma->content);
    int ib = vm_ctoi(mb->content);

    vm_itoc(ia/ib, ma->content);


}


