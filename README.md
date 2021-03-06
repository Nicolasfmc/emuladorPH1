# emulador PH1
### Trabalho de Arquitetura e Organização de Computadores I, Universidade de Passo Fundo

_Professor Mestre Marcos Jose Brusso_

_Nome: Nicolas Ferreira de Mello Costa_

_Matrícula: 178335_

#### Entrada
A entrada é composta por um arquivo-texto contendo uma série de linhas. Cada linha correspondente ao conteúdo inicial de um endereço da memória do PH1 e é representada por um endereço e um valor (ambos em hexadecimal) separados por um espaço em branco. Os valores iniciais de todos os endereços de memórias não informados, assim como de todos os registradores serão 00 (zero). O nome do arquivo de entrada não deve ser fixo dentro do programa, mas informado pelo usuário em tempo de execução.

**Exemplo de entrada (arquivo "entrada01.txt")**
```
00 10
01 81
02 30
03 82
04 20
05 80
06 F0
80 00 
81 05
82 02
```

#### Saída
A saída do programa deve ter exatamente o seguinte conteúdo:
* Uma linha com "Input file: " seguido do nome do arquivo de entrada
* Uma linha em branco
* Para cada instrução  executada* uma nova linha contendo:
  * O memônico da instrução em letras maiúsculas
  * Um espaço em branco.
  * O operando (se houver) em hexadecimal, com dois dígitos.
  * ";"
* Uma linha em branco
* N " instructions executed", onde N é o número total de instruções executadas.
* Uma linha em branco
* Uma linha contendo "Registers:"
* "AC: " seguido do valor final do registrador AC, em hexadecimal, com dois dígitos
* "PC: " seguido do valor final do registrador PC, em hexadecimal, com dois dígitos
* Uma linha em branco
* Uma linha contendo "Memory:"
* Para cada endereço de memória que tenha sido modificado (escrito) durante a execução do programa, uma linha contendo:
  * O endereço de memória, em hexadecimal, com dois dígitos
  * Um espaço em branco
  * O valor contido naquele endereço ao final da execução, em hexadecimal, com dois dígitos
  
*: Se a instrução estiver dentro de um laço deve aparecer e ser contada para cada vez que for executada. Se for uma instrução de desvio condicional, deve aparecer e ser contada mesmo que o desvio não tenha ocorrido. Intruções que tenham sido desviadas, sem serem buscadas, não aparecem nem contam.

#### Exemplo de saída para a entrada acima
```
Input file: entrada01.txt

LDR 81 ; AC <- MEM[81]
ADD 82 ; AC <- AC + MEM[82]
STR 80 ; MEM[80] <- AC
HLT

4 instructions executed

Registers:
AC 07
PC 07

Memory:
80 07
```
