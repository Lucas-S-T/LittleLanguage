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
    p->function = (void*)0;

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

long parser_get_as_integer(parser_T *p){

    long num = strtol(p->ct->content, NULL, 10);
    if (num == LONG_MAX){

        printf("Expected integer number in: %s\n", p->ct->content);
        exit(0);

    }


    return num;

}

float parser_get_as_float(parser_T *p){

    float num = strtof(p->ct->content, NULL);

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

    if(strcmp(p->ct->content, "FUN") == 0){
        return FUNCTION;
    }

    if(strcmp(p->ct->content, "RET") == 0){
        return RETURN;
    }
    if(strcmp(p->ct->content, "CALL") == 0){
        return CALL;
    }
    if(strcmp(p->ct->content, "PUSH") == 0){
        return PUSH;
    }
    if(strcmp(p->ct->content, "POP") == 0){
        return POP;
    }
    if(strcmp(p->ct->content, "INCLUDE") == 0){
        return INCLUDE;
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
            parser_verify_expected_or_die(p, NUMERIC_INT);
            long n = parser_get_as_integer(p);
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
            parser_verify_expected_or_die(p, NUMERIC_INT);
            long nl = parser_get_as_integer(p);
            i->larg0 = nl;
            parser_advance(p);
            break;

        case FUNCTION:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            i->funcID = p->ct->content;
            parser_advance(p);
            parser_verify_expected_or_die(p, COLON);
            parser_advance(p);

            break;

        case RETURN:

            break;

        case CALL:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case PUSH:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;

        case POP:

            parser_verify_expected_or_die(p, ID);
            i->carg0 = p->ct->content;
            parser_advance(p);

            break;
        case INCLUDE:

            parser_verify_expected_or_die(p, CHAR_SEQ);
            i->carg0 = p->ct->content;
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

                if(op == FUNCTION){

                    if(p->function != (void*)0){
                        printf("Invalid function declaration\n");
                        exit(0);
                    }

                    p->function = i->funcID;
                }

                i->funcID = p->function;

                if(op == RETURN){

                    if(p->function == (void*)0){
                        printf("RET instruction outside a FUN\n");
                        exit(0);
                    }

                    p->function = (void*)0;
                }

                return i;
            }
            break;


    }




    return i;

}





