; Exemplo de Hello World em Little Language

.CALL   HW                             ; Chama a função HW salvando a posição atual na stack de programa

.FUN    HW:                            ; Declara o inicio da função HW

           .ALC    A     11            ; Aloca 11 bytes em A
           .DS     A     "Hello World" ; Escreve "Hello World" em A
           .OUTS   A                   ; Imprime o conteúdo de A na tela
           .FREE   A                   ; Limpa a memória de A

.RET                                   ; Declara o final da função HW e retorna para posição anterior da stack de programa
