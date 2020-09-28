//
// Created by arch on 9/24/20.
//

#ifndef LITTLELANGUAGE_LL_H
#define LITTLELANGUAGE_LL_H

#include <zconf.h>

typedef struct LEXER_STRUCT{

    char *content;
    ulong size;
    ulong pos;
    char c;
    enum{

        NORMAL,
        COMMENT,
        QUOTE_OPENED

    }state;

}lexer_T;

typedef struct TOKEN_STRUCT{

    enum {

        ID,
        CHAR_SEQ,
        DOT,
        NUMERIC_INT,
        NUMERIC_FLOAT,
        COLON

    }type;


    // Only: NUMERIC, CHAR_SEQ, ID
    ulong size;
    char *content;

}token_t;


typedef struct PARSER_STRUCT{

    lexer_T *l;
    token_t *ct;
    enum{

        START,
        W_IOPCODE,

    }state;

    char *function;


}parser_T;


typedef struct INSTRUCTION_STRUCT{

  enum{

      ALLOCATE,
      DUMP_STRING,
      OUT_STRING,
      FREE,
      ALLOCATE_INT,
      LOAD_INT_CONST,
      OUT_INT,
      FUNCTION,
      RETURN,
      CALL,
      PUSH,
      POP


  }OPCODE;

  char *funcID;

  char *carg0;
  char *carg1;

  long larg0;
  long larg1;


}instruction_T;

typedef struct MEMORY_STRUCT{

    int used;
    char *id;
    ulong size;
    ulong fid;

    char content[];



}memory_T;


typedef struct STACK_STRUCT{

    ulong size;
    ulong top;
    void *stack[];

}stack_T;

typedef struct INSTRUCTION_SET_STRUCT{

    char *funcID;
    ulong sz;
    instruction_T *instructions[];


}instruction_set_T;

typedef struct VIRTUALMACHINE_STRUCT{

    parser_T *p;
    instruction_T *ci;
    ulong pc;

    stack_T *pcStack;
    stack_T *isStack;
    stack_T *fidStack;
    stack_T *generalStack;

    instruction_set_T *current_function;
    ulong current_function_id;

    ulong isSize;
    instruction_set_T *instruction_set[1024];

    memory_T *memory[1024];


}vm_T;







extern lexer_T *lexer_create(char *content, ulong size);
extern token_t *lexer_next_token(lexer_T *l);
extern parser_T *parser_create(lexer_T *l);
extern instruction_T *parser_next_instruction(parser_T *p);
extern vm_T *vm_create(parser_T *p);
extern int vm_run(vm_T *vm);



//      VM

//General
extern long vm_instruction_set_get_by_func_id_or_die(vm_T *v, char *funcID);
extern void vm_stack_push(stack_T *s, void *ptr);
extern void *vm_stack_pop(stack_T *s);
extern void *vm_stack_top(stack_T *s);


//Memory
extern memory_T *vm_memory_allocate_or_die(vm_T *v, char *id, ulong sz);
extern ulong vm_memory_find_index_by_id_or_die(vm_T *v, char *id);
extern ulong vm_next_free_memory_index_or_die(vm_T *v);
extern int vm_memory_free(vm_T *v, ulong index);
extern int vm_ctoi(char *c);
extern void vm_itoc(int i, char *c);
extern int vm_memory_is_allocated_by_id(vm_T *v, char *id);
extern void vm_memory_free_current_fid(vm_T *v);




//      Instructions

//Memory
extern void __allocate(vm_T *v, instruction_T *i);
extern void __free(vm_T *v, instruction_T *i);
extern void __allocate_int(vm_T *v, instruction_T *i);

//Output
extern void __out_string(vm_T *v, instruction_T *i);
extern void __out_int(vm_T *v, instruction_T *i);

//Functions
extern void __call(vm_T *v, instruction_T *i);
extern void __ret(vm_T *v, instruction_T *i);

//Stack
extern void __push(vm_T *v, instruction_T *i);
extern void __pop(vm_T *v, instruction_T *i);

//Variables
extern void __dump_string(vm_T *v, instruction_T *i);
extern void __load_int_const(vm_T *v, instruction_T *i);





#endif //LITTLELANGUAGE_LL_H
