
## Finite-state Machine
FSM is defined by
- finite set of state
- finite characters
- transition function
- starting state
- accepting state

### State
- empty
- equality
- parenthesis
- operator
- function
- number
- word

### Types of characters
- whitespaces
- equal sign
- parenthesis
- operators
- function
- number
- word(combination of alphabet and underscore)


## Tokenizer

### Table-based Scanner
- Character classifier table
- Transition table
- Token type table


## Transition Diagram

```mermaid
graph TD;
    start -- WS --> end
    start -- = --> end
    start -- ( --> end
    start -- +, -, *, /, ^ --> end
    start -- [1-9] --> nonzero_digit
    start -- 0 --> zero
    start -- ([a-z]|[A-Z]|_) --> word
    word -- ([a-z]|[A-Z]|[0-9]|_) --> word
    word -- WS, OP, . --> end
    zero -- . --> float
    zero -- [1-9] --> error
    zero -- WS, OP --> end
    nonzero_digit -- [0-9] --> nonzero_digit
    nonzero_digit -- . --> float
    nonzero_digit -- WS, OP, --> end
    float -- [0-9] --> float
    float -- WS, OP, . --> end
```
