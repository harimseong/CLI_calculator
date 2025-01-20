lowercase entry is non-terminal and uppercase entry is terminal.
terminal is represented in either string or regular expression.
```
input           : linebreak
                | assignment LINEBREAK // v2 feature
                | equation LINEBREAK
                | expression LINEBREAK
                ;
assignment      : VARIABLE '=' expression
                ;
equation        : expression '=' expression
                ;
expression      : term
                | additive_exp
                ;
additive_exp    : multiple_exp ADDITIVE_OP additive_exp
                | multiple_exp
                ;
multiple_exp    : power MULTIPLE_OP multiple_exp
                | power 
                ;
power           : term '^' power
                | term
                ;
term            : '(' term ')'
                | '(' UNARY_OP term ')'
                | '(' expression ')'
                | NUMBER
                | VARIABLE
                | function
                ;
function        : trigonometric // v2 feature
                ;
trigonometric   : 'cos(' expression ')'
                | 'sin(' expression ')'
                | 'tan(' expression ')'
                ;
UNARY_OP        : '+'
                | '-'
                ;
ADDITIVE_OP     : '+'
                | '-'
                ;
MULTIPLE_OP     : '*'
                | '/'
                ;
NUMBER          : (0|[1-9][0-9]*)           // integer
                | ([1-9][0-9]*|0).[0-9]*    // float
                ;
VARIABLE        : ([a-z]|[A-Z]|_)([0-9]|[a-z]|[A-Z]|_)*
                ;
LINEBREAK       : NEWLINE
                ;
```

removed Cycle term -> function -> power -> term
