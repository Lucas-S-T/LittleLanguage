; Exemplo de Hello World em Little Language

.FUN print_stack:           ; Declara a função print_stack

    .POP    hw              ; Puxa o conteúdo da Stack e salva em hw
    .OUTS   hw              ; Imprime o conteúdo de hw na tela
    .FREE   hw              ; Limpa a memória de hw

.RET                        ; Retorna a função print_stack


.ALC    sm  11              ; Aloca 11 bytes em sm
.DS     sm  "Hello World"   ; Escreve "Hello World" em sm
.PUSH   sm                  ; Joga o conteúdo na Stack
.FREE   sm                  ; Limpa a memória de sm
.CALL print_stack           ; Chama a função print_stack