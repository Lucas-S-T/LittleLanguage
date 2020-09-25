//
// Created by arch on 9/24/20.
//

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <lzma.h>
#include "ll.h"

parser_T *parser_create(lexer_T *l){

    parser_T *p = malloc(sizeof(struct PARSER_STRUCT));
    p->l = l;
    p->ct = lexer_next_token(l);

    return p;

}

void parser_advance(parser_T *p){

    p->ct = lexer_next_token(p->l);

}


int parser_verify_expected_or_die(parser_T *p, int type){

    if(p->ct->type == type){
        return 1;
    }else{

        printf("Unexpected token: %i. Expected: %i\n", p->ct->type, type);
        exit(0);
    }

}

long parser_get_as_integer_or_die(parser_T *p){

    long num = strtoll(p->ct->content, NULL, 10);
    if (num == LLONG_MAX){

        printf("Expected integer number in: %s\n", p->ct->content);
        exit(0);

    }


    return num;

}

int parser_get_opcode_or_die(parser_T *p){

    if(strcmp(p->ct->content, "ALC") == 0){
        return ALLOCATE;
    }

    if(strcmp(p->ct->content, "DS") == 0){
        return DUMP_STRING;
    }

    if(strcmp(p->ct->content, "OUTS") == 0){
        return OUT_STRING;
    }

    if(strcmp(p->ct->content, "FREE") == 0){
        return FREE;
    }

    if(strcmp(p->ct->content, "ALI") == 0){
        return ALLOCATE_INT;
    }

    if(strcmp(p->ct->content, "LIC") == 0){
        return LOAD_INT_CONST;
    }

    if(strcmp(p->ct->content, "OUTI") == 0){
        return OUT_INT;
    }

    printf("Unknown instruction: %s\n", p->ct->content);
    exit(0);

}

void parser_get_args_or_die(parser_T *p, instruction_T *i){

    switch (i->OPCODE) {

        case ALLOCATE:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);
            parser_verify_expected_or_die(p, ID);
            long n = parser_get_as_integer_or_die(p);
            if(n <=0){
                printf("Invalid or negative number in Allocate instruction.");
                exit(0);
            }
            i->larg0 = n;
            parser_advance(p);
            break;

        case DUMP_STRING:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);
            parser_verify_expected_or_die(p, CHAR_SEQ);
            i->carg1 = p->ct->content;
            parser_advance(p);

            break;

        case OUT_STRING:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case OUT_INT:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case FREE:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case ALLOCATE_INT:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case LOAD_INT_CONST:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);
            parser_verify_expected_or_die(p, ID);
            long nl = parser_get_as_integer_or_die(p);
            i->larg0 = nl;
            parser_advance(p);
            break;

    }




}

instruction_T *parser_next_instruction(parser_T *p){

    instruction_T *i = (void*)0;

    if(p->ct == (void*)0){
        return i;
    }


    switch (p->state) {

        case START:

            if(parser_verify_expected_or_die(p, DOT)){

                p->state = W_IOPCODE;
                parser_advance(p);
                return parser_next_instruction(p);

            }
            break;

        case W_IOPCODE:

            if(parser_verify_expected_or_die(p, ID)){

                int op = parser_get_opcode_or_die(p);
                i = malloc(sizeof(struct INSTRUCTION_STRUCT));
                i->OPCODE = op;
                parser_advance(p);
                parser_get_args_or_die(p, i);
                p->state = START;
                return i;
            }
            break;


    }




    return i;

}




