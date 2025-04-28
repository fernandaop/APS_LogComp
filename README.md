# APS_LogComp

1. Introdução:
  Essa é uma linguagem de programação criada como parte da APS de Log Comp feita por Fernanda Pereira.

2. Características
- Tipagem explícita (int, bool, string)
- Comandos de controle de fluxo: if, else, while
- Operações aritméticas (+, -, *, /)
- Operações relacionais (==, !=, <, >, <=, >=)
- Impressão de valores com print

3. Gramática - EBNF
```
(* Programa: sequência de comandos *)
program           = { statement } ;

(* Comandos *)
statement         = variable_declaration
                  | assignment
                  | if_statement
                  | while_statement
                  | print_statement ;

(* Declaração de variáveis *)
variable_declaration = "var" identifier ":" type "=" expression ";" ;

(* Atribuição *)
assignment        = identifier "=" expression ";" ;

(* Condicional IF/ELSE *)
if_statement      = "if" "(" condition ")" "{" { statement } "}" [ "else" "{" { statement } "}" ] ;

(* Laço WHILE *)
while_statement   = "while" "(" condition ")" "{" { statement } "}" ;

(* Impressão *)
print_statement   = "print" "(" expression ")" ";" ;

(* Expressões aritméticas *)
expression        = term { ("+" | "-") term } ;

term              = factor { ("*" | "/") factor } ;

factor            = number
                  | string
                  | boolean
                  | identifier
                  | "(" expression ")" ;

(* Condições booleanas *)
condition         = expression comparison_operator expression ;

comparison_operator = "==" | "!=" | "<" | "<=" | ">" | ">=" ;

(* Tipos de variáveis *)
type              = "int" | "bool" | "string" ;

(* Identificadores e valores *)
identifier        = letter { letter | digit | "_" } ;

number            = digit { digit } ;

string            = '"' { character } '"' ;

boolean           = "true" | "false" ;

(* Caracteres *)
letter            = "a" | "b" | ... | "z" | "A" | "B" | ... | "Z" ;

digit             = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

character         = letter | digit | symbol ;

symbol            = "!" | "@" | "#" | "$" | "%" | "^" | "&" | "*" | "(" | ")" 
                  | "-" | "_" | "+" | "=" | "{" | "}" | "[" | "]" | ":" | ";" 
                  | "'" | "<" | ">" | "," | "." | "/" | "?" | "\\" | "|" ;
```

4. Exemplo de Código
```
var x: int = 5;
var y: int = 10;
var texto: string = "Olá Mundo";

if (x < y) {
    print(texto);
} else {
    print("Erro");
}

while (x < 10) {
    x = x + 1;
    print(x);
}
```
