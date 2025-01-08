lowercase entry is non-terminal and uppercase entry is terminal.
terminal is represented in either string or regular expression.
```
input           : linebreak
                | equation linebreak
                | assignment linebreak // v2 feature
                | expression linebreak
                ;
equation        : expression '=' expression
                ;
assignment      : VARIABLE '=' expression
                ;
expression      : term
                | additive_exp
                ;
additive_exp    : multiple_exp
                | multiple_exp additive_op additive_exp
                ;
multiple_exp    : term
                | term multiple_op multiple_exp
                ;
term            : '(' term ')'
                | '(' UNARY_OP term ')'
                | '(' expression ')'
                | NUMBER
                | VARIABLE
                | function
                ;
function        : power
                | trigonometric // v2 feature
                ;
power           : term '^' term
                ;
trigonometric   : 'cos(' expression ')'
                | 'sin(' expression ')'
                | 'tan(' expression ')'
                ;
UNARY_OP        : '-'
                | '+'
                ;
additive_op     : unary_op
                ;
multiple_op     : '*'
                | '/'
                ;
NUMBER          : [1-9][0-9]*               // integer
                | ([1-9][0-9]*|0).[0-9]*    // float
                ;
VARIABLE        : ([a-z]|[A-Z]|_)([0-9]|[a-z]|[A-Z]|_)*
                ;
linebreak       : NEWLINE
                ;
```
