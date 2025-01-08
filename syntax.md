lowercase entry is non-terminal and uppercase entry is terminal.
```
input           : linebreak
                | expression linebreak
                ;
expression      : additive_exp
                | term
                ;
additive_exp    : multiple_exp
                | multiple_exp additive_op additive_exp
                ;
multiple_exp    : term
                | term multiple_op multiple_exp
                ;
term            : '(' UNARY_OP term ')'
                | '(' expression ')'
                | NUMBER
                | VARIABLE
                | function
                ;
function        : power
                | trigonometric
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
VARIABLE        : [a-z]([0-9]|[a-z]|_)*
                ;
linebreak       : NEWLINE
                ;
```
