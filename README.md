# Little Language

Little Language é uma linguagem de programação desenvolvima em cima de C para fins educacionais.

Meu objetivo principal quando criei esse projeto era entender melhor o gerenciamento de memória,
análises léxicas e o funcionamento de um compilador. Nesse 
projeto é possível encontrar um Analisador Léxico, Analisador Sintático e uma Máquina Virtual.

O objetivo final dessa linguagem é ser uma linguagem com Completude de Turing, ou seja:
Um sistema computacional que pode computar todas as funções Turing-computáveis, alternativamente, 
tal sistema é aquele que pode simular uma máquina de Turing universal.

# Instalação

Necessário CMake 3.17 +

Testado apenas em um ambiente Arch Linux com 64 bits.

```

~/$ git clone https://github.com/Lucas-S-T/LittleLanguage
~/$ cd LittleLanguage
~/LittleLanguage$ cmake .
~/LittleLanguage$ cmake --build .
~/LittleLanguage$ cmake --install .


~/LittleLanguage$ LittleLanguage hello_world.ll
```

# Documentação

 - [Wiki](https://github.com/Lucas-S-T/LittleLanguage/wiki/)
 - [Máquina Virtual](https://github.com/Lucas-S-T/LittleLanguage/wiki/M%C3%A1quina-Virtual)
 - [Instruções](https://github.com/Lucas-S-T/LittleLanguage/wiki/Instru%C3%A7%C3%B5es)


# Exemplo Hello World

```
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

```


# TODO

## Maquina Virtual

- [x] Melhorar conversão de char[] para int e outros tipos.
- [ ] Outros tipos primitivos.
- [x] Suporte a Pilhas(Stacks, Geral, Calls etc).
- [x] Pre-carregamento das instruções.
- [x] Contador de programa (PC).
- [x] Verificar se uma variável existe antes de efetuar uma operação.
- [x] Escopo de variáveis em funções.
- [x] Limpar a memória das variáveis ao retornar uma funcão.
- [ ] Tamanho dinâmico da stack e memória (Limite atual de 1024)

## Instruções

- [ ] Operações aritméticas básicas.
- [ ] Operações lógicas básicas.
- [ ] Pulos condicionais.
- [ ] Pulos relativos.
- [x] Chamadas de funções.
- [x] Retorno de funções.


## Analisador Léxico

- [x]  Identificar números decimais e inteiros.

## Analisador Sintático

- [x] Suporte a declaração de funções.
- [x] Suporte para incluir múltiplos arquivos.

## Geral

- [ ] Melhorar mensagens de erro do Lexador e Analisador.
- [ ] Completude de Turing.
 
 
 
