//
// Created by arch on 9/25/20.
//
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "ll.h"

vm_T *vm_create(parser_T *p){

    vm_T *v = malloc(sizeof(struct VIRTUALMACHINE_STRUCT));
    v->p = p;
    v->ci = parser_next_instruction(p);

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){
        v->memory[i] = (void*)0;
    }

    return v;

}

void vm_advance(vm_T *vm){
    vm->ci = parser_next_instruction(vm->p);
}


ulong vm_next_free_memory_index_or_die(vm_T *v){

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){
        if(v->memory[i] == (void*)0 || v->memory[i]->used == 0){
            return i;
        }
    }

    printf("Out of memory.");
    exit(0);

}

memory_T *vm_memory_allocate(vm_T *v, char *id, ulong sz){

    memory_T *m = malloc(sizeof(struct MEMORY_STRUCT)+sz);
    m->id = id;
    m->size = sz;
    m->used = 1;

    v->memory[vm_next_free_memory_index_or_die(v)] = m;

    return m;

}

ulong vm_memory_find_index_by_id(vm_T *v, char *id){

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){

        if(v->memory[i] != (void*)0 && strcmp(v->memory[i]->id, id) == 0){
            return i;
        }

    }

    return ULONG_MAX;

}

int vm_memory_free(vm_T *v, ulong index){

    memory_T *m = v->memory[index];

    free(m);

    v->memory[index] = (void*)0;

    return 1;
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


void __allocate(vm_T *v, instruction_T *i){

    ulong sz = i->larg0;
    char *id = i->carg0;

    vm_memory_allocate(v, id, sz);

}


void __dump_string(vm_T *v, instruction_T *i){

    char *mid = i->carg0;
    char *cont = i->carg1;

    ulong mi = vm_memory_find_index_by_id(v, mid);

    if(mi == ULONG_MAX){
        printf("Memory %s not allocated\n", mid);
        exit(0);
    }

    memory_T *m = v->memory[mi];

    for(int j = 0; j<strlen(cont); j++){
        m->content[j] = cont[j];
    }


}

void __out_string(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id(v, mid);

    if(mi == ULONG_MAX){
        printf("Memory %s not allocated\n", mid);
        exit(0);
    }

    memory_T *m = v->memory[mi];

    printf("%s\n", m->content);

}


void __free(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id(v, mid);

    if(mi == ULONG_MAX){
        printf("Memory %s not allocated\n", mid);
        exit(0);
    }

  vm_memory_free(v, mi);

}

void __allocate_int(vm_T *v, instruction_T *i){

    char *id = i->carg0;

    vm_memory_allocate(v, id, 4);

}

void __load_int_const(vm_T *v, instruction_T *i){

    ulong cont = i->larg0;
    char *id = i->carg0;

    ulong mi = vm_memory_find_index_by_id(v, id);

    if(mi == ULONG_MAX){
        printf("Memory %s not allocated\n", id);
        exit(0);
    }

    memory_T *m = v->memory[mi];


    vm_itoc(cont, m->content);

}


void __out_int(vm_T *v, instruction_T *i){

    char *mid = i->carg0;

    ulong mi = vm_memory_find_index_by_id(v, mid);

    if(mi == ULONG_MAX){
        printf("Memory %s not allocated\n", mid);
        exit(0);
    }

    memory_T *m = v->memory[mi];

    int vl = vm_ctoi(m->content);

    printf("%i\n", vl);

}

void vm_execute_instruction(vm_T *vm, instruction_T *i){

    switch (i->OPCODE) {

        case ALLOCATE:
            __allocate(vm, i);
            break;
        case DUMP_STRING:
            __dump_string(vm ,i);
            break;
        case OUT_STRING:
            __out_string(vm, i);
            break;
        case FREE:
            __free(vm, i);
            break;
        case ALLOCATE_INT:
            __allocate_int(vm, i);
            break;
        case LOAD_INT_CONST:
            __load_int_const(vm, i);
            break;
        case OUT_INT:
            __out_int(vm, i);
            break;

    }


}


int vm_run(vm_T *vm){



      while(vm->ci != (void*)0){

            vm_execute_instruction(vm, vm->ci);

          vm_advance(vm);
      }



    return 0;
}