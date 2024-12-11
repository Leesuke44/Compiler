# Compiler
The compiler program, can compile declarations, assigments, if-else conditions, and loops. Use Lex to construct scanner and use Yacc to construct parser. 
## Source code
## Result
```
START MyFirstProgram
Declare A, Integer_array, 100
Declare B, Integer
Declare C, Integer
Declare D, Integer
Declare I, Integer
Declare J, Integer
Declare E, Float_array, 50
Declare F, Float
Declare G, Float
Declare H, Float
I_STORE 1, I
lb&0:    Declare T1, Integer
F_DIV I, 2, T&0
I_STORE T&0, T1
I_ADD A[I], A[T], T&1
F_MUL B, C, T&2
F_DIV T&2, D, T&3
I_SUB T&1, T&3, T&4
I_STORE T&4, A[I]
INC I
I_CMP I, 100
JLE lb&0
I_STORE 50, J
lb&1:    Declare T2, Integer
F_DIV J, 2, T&5
I_STORE T&5, T2
F_DIV E[I], E[J], T&6
F_MUL T&6, F, T&7
F_SUB T&7, G, T&8
F_ADD T&8, H, T&9
F_STORE T&9, E[J]
DEC J
I_CMP J, 1
JGE lb&1
HALT MyFirstProgram
```
