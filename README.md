# Command-line Calculator
This is a command-line calculator implemented on backtrack-free recursive descent parser(RDP). Except that it examines equal sign to identify and solve equation, it is LL(1) parser.
Purpose of the project is getting familiar with compiler frontend elements such as tokenizer, parser and AST.

## Tokenizer
Useful concepts for understanding and implementing tokenizer(or lexer or scanner).

### Finite-state Machine
FSM is defined by
- finite set of state
- finite characters
- transition function
- starting state
- accepting state

### Table-based Scanner
- Character classifier table 

    defines category of characters.
    e.g) \*, +, -, / belong to operator, alphabet belong to alphabet.
- Transition table

    Map a pair of a state and a character to next state.
- Token type table

    One of the token types is assigned to an acquired token.

## Transition Diagram

### States
- whitespaces
- minus
- operators
- parenthesis
- zero
- nonzero_digits
- floating
- word
- error

### Types of characters
- whitespace
- paren
- minus -
- op (=|+|\*|/)
- zero 0
- nonzero_digit [1-9]
- dot .
- word_starter ([a-z]|[A-Z]|\_)
- char [a-z]|[A-Z]|[0-9]|\_)
- invalid


A state -- a type of character --> next state
```mermaid
graph TD;
    start -- whitespace --> whitespaces
    start -- minus --> minus
    start -- op --> operators
    start -- paren --> parenthesis
    start -- zero --> zero
    start -- nonzero_digit --> nonzero_digits
    start -- word_starter --> word

    whitespaces -- whitespace --> whitespaces
    zero -- dot --> floating
    nonzero_digits -- dot --> floating
    nonzero_digits -- digit --> nonzero_digits
    floating -- digit --> floating
    word -- char --> word

    whitespaces --> accept
    minus --> accept
    operators --> accept
    parenthesis --> accept
    zero --> accept
    nonzero_digits --> accept
    floating --> accept
    word --> accept
```

## Tokenizer Logic
0. Initialize a stack.
1. Take a character from input stream. If there's no character to read, jump to 4.
2. Look at the transition table.
    1. If next state is an error, jump to 4.
    2. Else if next state is acceptable, jump to 3.
3. Clear the stack and push the current state and jump to 1.
4. Decrement input stream pointer by one and pop a state from the stack.
    1. If the state is acceptable or the stack is empty, jump to 5.
    2. Else if the state is error, jump to 4.
5. return the final state.

## Parser

### BNF for parsing rules
lowercase entry is non-terminal and uppercase entry is terminal.
terminal is represented in either string or regular expression.
```
input           : LINEBREAK
                | expression LINEBREAK
                ;
expression      : equation    
                | simple_exp
                ;
equation        : VARIABLE '=' expression
                | expression '=' expression
                ;
simple_exp      : additive_exp
                ;
additive_exp    : multiple_exp ADDITIVE_OP additive_exp
                | multiple_exp
                ;
multiple_exp    : power MULTIPLE_OP multiple_exp
                | power 
                ;
power           : unary_exp '^' power
                | unary_exp
                ;
unary_exp       : UNARY_OP term
                | term
                ;
term            : '(' expression ')'
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
ADDITIVE_OP     : '+'
                | '-'
                ;
UNARY_OP        : '+'
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
### Bugfix
- removed Cycle: term -> function -> power -> term

## Reference
Engineering a compiler by Kenith D. Cooper
