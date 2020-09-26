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
        NUMERIC_FLOAT

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


}parser_T;


typedef struct INSTRUCTION_STRUCT{

  enum{

      ALLOCATE,
      DUMP_STRING,
      OUT_STRING,
      FREE,
      ALLOCATE_INT,
      LOAD_INT_CONST,
      OUT_INT


  }OPCODE;


  char *carg0;
  char *carg1;

  long larg0;
  long larg1;


}instruction_T;

typedef struct MEMORY_STRUCT{

    int used;
    char *id;
    ulong size;

    char content[];



}memory_T;

typedef struct VIRTUALMACHINE_STRUCT{

    parser_T *p;
    instruction_T *ci;

    memory_T *memory[1024];


}vm_T;




extern lexer_T *lexer_create(char *content, ulong size);
extern token_t *lexer_next_token(lexer_T *l);
extern parser_T *parser_create(lexer_T *l);
extern instruction_T *parser_next_instruction(parser_T *p);
extern vm_T *vm_create(parser_T *p);
extern int vm_run(vm_T *vm);

#endif //LITTLELANGUAGE_LL_H
