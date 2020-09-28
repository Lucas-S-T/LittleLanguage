//
// Created by arch on 9/25/20.
//
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "ll.h"

stack_T *vm_stack_create(ulong size){

    stack_T *s = malloc(sizeof(struct STACK_STRUCT)+sizeof(void*)*size);
    s->top = 0;
    s->size = size;
    return s;

}

long vm_instruction_set_create(vm_T *vm, char *funcID){

    instruction_set_T *is = malloc(sizeof(struct INSTRUCTION_SET_STRUCT));
    is->sz = 0;
    is->funcID = funcID;

    vm->instruction_set[vm->isSize] = is;
    vm->isSize++;

    return vm->isSize-1;
}

instruction_set_T *vm_instruction_set_add(instruction_set_T *is, instruction_T *i){

    instruction_set_T *isc;

    isc = realloc(is, sizeof(instruction_set_T)+sizeof(void*)*(is->sz+1));
    isc->instructions[isc->sz] = i;
    isc->sz++;
    return isc;

}


long vm_instruction_set_get_by_func_id_or_die(vm_T *v, char *funcID){

    for(long i = 0; i<v->isSize; i++){

        if(funcID == v->instruction_set[i]->funcID || ( funcID != (void*)0 && v->instruction_set[i]->funcID != (void*)0  && strcmp(funcID, v->instruction_set[i]->funcID) == 0)){
            return i;
        }

    }

    printf("Invalid function %s\n", funcID);
    exit(0);

}

int vm_instruction_set_verify_func_id_exists(vm_T *v, char *funcID){

    for(long i = 0; i<v->isSize; i++){

        if(funcID == v->instruction_set[i]->funcID || ( funcID != (void*)0 && v->instruction_set[i]->funcID != (void*)0  && strcmp(funcID, v->instruction_set[i]->funcID) == 0)){
            return 1;
        }

    }

    return 0;

}

void vm_advance(vm_T *vm){
    vm->ci = parser_next_instruction(vm->p);
}

void vm_load_instructions(vm_T *vm){

    instruction_T *i = vm->ci;

    instruction_set_T *cs;

    long ind = vm_instruction_set_create(vm, (void*)0);
    cs = vm->instruction_set[ind];

    while(i != (void*)0){

        if(vm->ci->OPCODE == FUNCTION){

            if(vm_instruction_set_verify_func_id_exists(vm, vm->ci->funcID) == 0){

                ind =  vm_instruction_set_create(vm, vm->ci->funcID);
                cs = vm->instruction_set[ind];

            }else{
                printf("Duplicated function name declaration\n");
            }

            vm_advance(vm);
            i = vm->ci;
            continue;
        }


        vm->instruction_set[ind] = vm_instruction_set_add(cs, vm->ci);
        cs = vm->instruction_set[ind];



        if(vm->ci->OPCODE == RETURN){
            ind = vm_instruction_set_get_by_func_id_or_die(vm, (void*)0);
            cs = vm->instruction_set[ind];

        }

        vm_advance(vm);
        i = vm->ci;
    }



    ind = vm_instruction_set_get_by_func_id_or_die(vm, (void*)0);

    cs = vm->instruction_set[ind];

    vm->current_function = cs;

}

instruction_T *vm_next_instruction(vm_T *vm){

    instruction_set_T *cf = vm->current_function;

    if(cf->sz == vm->pc){
        return (void*)0;
    }

    vm->pc++;

    return cf->instructions[vm->pc-1];

}

vm_T *vm_create(parser_T *p){

    vm_T *v = malloc(sizeof(struct VIRTUALMACHINE_STRUCT));
    v->p = p;
    v->ci = parser_next_instruction(p);

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){
        v->memory[i] = (void*)0;
    }

    v->pc = 0;

    v->pcStack = vm_stack_create(1024);
    v->isStack = vm_stack_create(1024);
    v->generalStack = vm_stack_create(1024);

    vm_load_instructions(v);

    return v;

}



void vm_stack_push(stack_T *s, void *ptr){

    if(s->size == s->top){
        printf("Stack Overflow\n");
        exit(0);
    }

    s->stack[s->top++] = ptr;

}

void *vm_stack_pop(stack_T *s){

    if(s->top == 0){
        printf("Stack Underflow\n");
        exit(0);
    }

    return s->stack[--s->top];

}

void *vm_stack_top(stack_T *s){

    return s->stack[s->top-1];

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

memory_T *vm_memory_allocate_or_die(vm_T *v, char *id, ulong sz){

    if(vm_memory_is_allocated_by_id(v, id)){
        printf("Memory %s is already allocated", id);
        exit(0);
    }

    memory_T *m = malloc(sizeof(struct MEMORY_STRUCT)+sz);
    m->id = id;
    m->size = sz;
    m->used = 1;

    v->memory[vm_next_free_memory_index_or_die(v)] = m;

    return m;

}

ulong vm_memory_find_index_by_id_or_die(vm_T *v, char *id){

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){

        if(v->memory[i] != (void*)0 && strcmp(v->memory[i]->id, id) == 0){
            return i;
        }

    }

    printf("Memory %s not allocated.", id);
    exit(0);


}

int vm_memory_is_allocated_by_id(vm_T *v, char *id){

    for(int i = 0; i<sizeof(v->memory)/sizeof(void*); i++){

        if(v->memory[i] != (void*)0 && strcmp(v->memory[i]->id, id) == 0){
            return 1;
        }

    }

    return 0;

}

int vm_memory_free(vm_T *v, ulong index){

    memory_T *m = v->memory[index];

    free(m);

    v->memory[index] = (void*)0;

    return 1;
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
        case CALL:
            __call(vm, i);
            break;
        case RETURN:
            __ret(vm, i);
            break;
        case PUSH:
            __push(vm, i);
            break;
        case POP:
            __pop(vm, i);
            break;

    }


}


int vm_run(vm_T *vm){


    instruction_T *i = vm_next_instruction(vm);

    while(i != (void*)0){

        vm_execute_instruction(vm, i);

        i = vm_next_instruction(vm);
    }


    return 0;
}