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

```

~/$ git clone https://github.com/Lucas-S-T/LittleLanguage
~/$ cd LittleLanguage
~/LittleLanguage$ cmake .
~/LittleLanguage$ cmake --build .
~/LittleLanguage$ cmake --install .


~/LittleLanguage$ LittleLanguage hello_world.ll
```

# Máquina Virtual

Little Language é uma linguagem interpretada que roda em uma Máquina Virtual, sendo capaz
de simular: uma Memória Virtual, um Contador de Programa, múltiplas Pilhas(Stacks) e diferentes
Conjuntos de Instruções.

### Memória

Diferente de um computador normal, Little Language tem uma forma diferente de gerenciar a memória,
a Máquina Virtual é equipada com 1024 diferentes ponteiros de memória, ou seja, você poderá alocar apenas
1024 variáveis ao mesmo tempo, porém, não há limites de quantos bytes pode ser alocado em um único
ponteiro (Claro, o limite é sua quantidade de RAM).


# Tabela de instruções

Use o caracter .(ponto) antes de cada instrução.

|Nome Completo|OpCode|Argumentos|Exemplo|Descrição|
|----|------|----------|-------|---------|
|Allocate |ALC   | (2) ID, SIZE| ALC HW 11 | Aloca 11 bytes no endereço de memória de HW|
|Free|FREE  | (1) ID   | FREE HW| Libera a memória alocada em HW|
|Dump String | DS | (2) ID, STR | DS HW "Hello World"| Salva "Hello World" em HW|
|Out String | OUTS | (1) ID | OUTS HW | Imprime o conteúdo de HW na tela |
|Allocate Int |ALI | (1) ID | ALI HW | Aloca 4 bytes no endereço de memória de HW|
|Load Int Const| LIC | (2) ID, INT | LIC HW 2 |Salva o valor inteiro constante 2 em HW |
|Out Int | OUTI | (1) ID | OUTS HW | Imprime o conteúdo de HW na tela em decimal|
|Function | FUN | (1) ID | FUN HW: | Declara uma função com o nome HW|
|Return | RET | (0) | RET | Retorna a função|
|Call Function | CALL | (1) ID | CALL HW | Chama a função HW|



# Exemplo Hello World

```
; Exemplo de Hello World em Little Language

.CALL   HW                             ; Chama a função HW salvando a posição atual na stack de programa

.FUN    HW:                            ; Declara o inicio da função HW

           .ALC    A     11            ; Aloca 11 bytes em A
           .DS     A     "Hello World" ; Escreve "Hello World" em A
           .OUTS   A                   ; Imprime o conteúdo de A na tela
           .FREE   A                   ; Limpa a memória de A

.RET                                   ; Declara o final da função HW e retorna para posição anterior da stack de programa
```



# TODO

## Maquina Virtual

- [x] Melhorar conversão de char[] para int e outros tipos.
- [ ] Outros tipos primitivos.
- [x] Suporte a Pilhas(Stacks, Geral, Calls etc).
- [x] Pre-carregamento das instruções.
- [x] Contador de programa (PC).
- [ ] Verificar se uma variável existe antes de efetuar uma operação.
- [ ] Escopo de variáveis em funções.

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
- [ ] Suporte para incluir múltiplos arquivos.

## Geral

- [ ] Melhorar mensagens de erro do Lexador e Analisador.
- [ ] Completude de Turing.
 
 
 
