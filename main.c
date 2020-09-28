#include <stdio.h>
#include <stdlib.h>
#include "ll.h"

int main(int args, char **argv) {

    if(args <2){

        printf("Please use %s <filename>\n", argv[0]);
        exit(0);

    }

    FILE *f = fopen(argv[1], "rb");

    if(f == (void*)0){
        printf("File not found\n");
        exit(0);
    }


    fseek(f, 0, SEEK_END);

    ulong sz = ftello(f);

    char *code = calloc(1, sz+1);

    fseek(f, 0, SEEK_SET);

    fread(code, sz, 1, f);

    code[sz] = '\0';

    lexer_T *l = lexer_create(code, sz, argv[0]);
    parser_T *p = parser_create(l);


    vm_T *vm = vm_create(p);
    return vm_run(vm);


}
