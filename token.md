
## Finite-state Machine
FSM is defined by
- finite set of state
- finite characters
- transition function
- starting state
- accepting state


## Tokenizer

### Table-based Scanner
- Character classifier table
- Transition table
- Token type table


## Transition Diagram

### States
- whitespaces
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
- op (=|+|-|\*|/)
- starting_zero ^0
- nonzero_digit [1-9]
- digit [0-9]
- dot .
- starting_char ^([a-z]|[A-Z]|\_)
- character [a-z]|[A-Z]|[0-9]|\_)
- invalid


```mermaid
graph TD;
    start -- whitespace --> whitespaces
    start -- op --> operators
    start -- paren --> parenthesis
    start -- starting_zero --> zero
    start -- nonzero_digit --> nonzero_digits
    start -- starting_char --> word
    whitespaces -- whitespace --> whitespaces
    zero -- dot --> floating
    nonzero_digits -- dot --> floating
    nonzero_digits -- digit --> nonzero_digits
    nonzero_digits -- digit --> accept
    floating -- digit --> floating
    word -- character --> word
    whitespaces --> accept
    operators --> accept
    parenthesis --> accept
    zero --> accept
    nonzero_digits --> accept
    floating --> accept
    word --> accept
```
