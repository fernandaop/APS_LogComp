# APS_LogComp

1. Introdução:
  Essa é uma linguagem de programação criada como parte da APS de Log Comp feita por Fernanda Pereira.

2. Características
- **Tipagem explícita** com valor padrão (`:=`)
- **Loop com contador embutido** (`loop var in range`)
- **Impressão reativa** com `watch`
- **Decisão como expressão funcional** (`decide`)
- **Blocos organizacionais nomeados** (`section`)
- **Retornos intermediários fora de funções** (`yield`)
- Impressão de saída com `show`
- Tipos: `int`, `bool`, `text`
- Booleanos com `yes` e `no`

3. Gramática - EBNF
```ebnf
(* Programa completo *)
program              = { block } ;

(* Blocos nomeados *)
block                = ["section" identifier ":"] { statement } ;

(* Comandos *)
statement            = variable_declaration
                     | assignment
                     | if_expression
                     | loop_statement
                     | watch_statement
                     | yield_statement
                     | print_statement
                     | ";" ;

(* Declaração de variáveis com valor padrão *)
variable_declaration = "let" identifier ":" type ":=" expression ";" ;

(* Atribuição *)
assignment           = identifier "<-" expression ";" ;

(* Impressão padrão *)
print_statement      = "show" "(" expression ")" ";" ;

(* Impressão reativa *)
watch_statement      = "watch" identifier ";" ;

(* Condicional como expressão *)
if_expression        = "decide" "(" condition "," expression_if_true "," expression_if_false ")" ;

(* Loop com contador implícito *)
loop_statement       = "loop" identifier "in" "range" "(" expression "," expression ")" "{" { statement } "}" ;

(* Retorno intermediário de valor *)
yield_statement      = "yield" expression ";" ;

(* Expressões *)
expression           = term { ("+" | "-" | "++") term } ;

term                 = factor { ("*" | "/" | "//") factor } ;

factor               = number | string | boolean | identifier | "(" expression ")" ;

(* Condições *)
condition            = expression comparison_operator expression ;

comparison_operator  = "==" | "!=" | "<" | "<=" | ">" | ">=" ;

(* Tipos *)
type                 = "int" | "bool" | "text" ;

(* Valores e identificadores *)
identifier           = letter { letter | digit | "_" } ;

number               = digit { digit } ;

string               = '"' { character } '"' ;

boolean              = "yes" | "no" ;

letter               = "a" | ... | "z" | "A" | ... | "Z" ;

digit                = "0" | ... | "9" ;

character            = letter | digit | symbol ;

symbol               = any printable ASCII symbol ;
```

4. Exemplo de Código
```
section intro:
    let nome: text := "Fernanda";
    let pontos: int := 0;

    show("Bem-vinda, " ++ nome);

section contagem:
    loop i in range(0, 3) {
        show("Rodada: " ++ i);
        pontos <- pontos + 10;
        watch pontos;
    }

section decisao:
    let status: text := decide(pontos >= 30, "Aprovada", "Reprovada");
    yield status;

```
