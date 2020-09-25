//
// Created by arch on 9/24/20.
//

#include <stdlib.h>
#include <stdio.h>
#include "ll.h"


lexer_T *lexer_create(char *content, ulong size){

    lexer_T *l = malloc(sizeof(struct LEXER_STRUCT));

    l->content = content;
    l->size = size;
    l->pos = 0;
    l->c = l->content[l->pos];
    l->state = NORMAL;

    return l;

}


void lexer_advance(lexer_T *l){

    if(l->size > l->pos) {
        l->c = l->content[++l->pos];
    } else {

        if(l->state == QUOTE_OPENED){
            printf("[Lexer] Error, quotes opened but not closed.");
            exit(0);
        }

    }

}


void lexer_get_until_char(lexer_T *l, token_t *t, char c){

    ulong ptr = 0;

    while(l->c != c){

        if(t->size == ptr+1){
            t->size *=2;
            t->content = realloc(t->content, t->size);
        }

        t->content[ptr] = l->c;
        t->content[ptr+1] = '\0';
        lexer_advance(l);
        ptr++;
    }


}

void lexer_get_until_chars(lexer_T *l, token_t *t, char *c, int sz){

    ulong ptr = 0;

    do{

        for(int i = 0; i< sz; i++){
            if(c[i] == l->c){
                return;
            }
        }

        if(t->size == ptr+1){
            t->size *=2;
            t->content = realloc(t->content, t->size);
        }

        t->content[ptr] = l->c;
        t->content[ptr+1] = '\0';
        lexer_advance(l);
        ptr++;

    }while(1);


}


token_t *lexer_next_token(lexer_T *l){

    char *c = &l->c;

    token_t *t = (void*)0;


    while (l->state == COMMENT){

        if(*c == '\n'){
            l->state = NORMAL;
            lexer_advance(l);
            break;
        }
        lexer_advance(l);

    }


    switch (*c) {

        case ' ':
            lexer_advance(l);
            return lexer_next_token(l);

        case '\n':
            lexer_advance(l);
            return lexer_next_token(l);

        case ';':
            l->state = COMMENT;
            lexer_advance(l);
            return lexer_next_token(l);

        case '.':

            t = malloc(sizeof(struct TOKEN_STRUCT));
            t->type = DOT;
            lexer_advance(l);

            break;

        case '"':

            t = malloc(sizeof(struct TOKEN_STRUCT));
            l->state = QUOTE_OPENED;
            lexer_advance(l);
            t->content = malloc(8);
            t->size = 8;
            t->type = CHAR_SEQ;
            lexer_get_until_char(l, t, '"');
            l->state = NORMAL;
            lexer_advance(l);
            break;

        case '\0':

            break;

        default:

            t = malloc(sizeof(struct TOKEN_STRUCT));
            t->content = malloc(8);
            t->size = 8;
            t->type = ID;
            char cf[4] = " \n;\0";
            lexer_get_until_chars(l, t, cf, 4);
            break;



    }


    return t;
}
