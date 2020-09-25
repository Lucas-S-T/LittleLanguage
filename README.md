# Little Language

Little Language é uma linguagem de programação desenvolvima em cima de C para fins educacionais.

Meu objetivo principal quando criei esse projeto era entender melhor o gerenciamento de memória,
análises léxicas e o funcionamento de um compilador. Nesse 
projeto é possível encontrar um Analisador Léxico, Analisador Sintático e uma Máquina Virtual.


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



# Exemplo Hello World

```

; Exemplo de Hello World em Little Language

.ALC    A     11            ; Aloca 11 bytes em A
.DS     A     "Hello World" ; Escreve "Hello World" em A
.OUTS   A                   ; Imprime o conteúdo de A na tela
.FREE   A                   ; Limpa a memória de A

```



# TODO

## Maquina Virtual

- [ ] Melhorar conversão de char[] para int e outros tipos.
- [ ] Outros tipos primitivos.
- [ ] Suporte a Pilhas(Stacks, Geral, Calls etc).
- [ ] Pre-carregamento das instruções.
- [ ] Contador de programa (PC).

## Instruções

- [ ] Operações aritméticas básicas.
- [ ] Operações lógicas básicas.
- [ ] Pulos condicionais.
- [ ] Pulos relativos.
- [ ] Chamadas de funções.
- [ ] Retorno de funções.


## Analisador Léxico

- [ ]  Identificar números decimais e inteiros (Atualmente no Analisador Sintático).

## Analisador Sintático

- [ ] Suporte a declaração de funções.

## Geral

- [ ] Melhorar mensagens de erro do Lexador e Analisador.
 
 
 
