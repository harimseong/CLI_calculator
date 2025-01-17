##### Types of characters
- whitespaces
- equal sign
- parenthesis
- operators
- function
- number
- word(combination of alphabet and underscore)

### Finite-state Machine
FSM is defined by
- finite set of state
- finite characters
- transition function
- starting state
- accepting state

#### State
- empty
- equality
- parenthesis
- operator
- function
- number
- word

#### Transition Function

### Tokenizer

#### Table-based Scanner
- Character classifier table
- Transition table
- Token type table


### Transition Diagram

```mermaid
graph TD;
    empty -- whitespace --> empty
    empty -- = --> equality
    empty -- ( --> parenthesis
    empty -- +, -, *, /, ^ --> operators
    empty -- [0-9] --> number
    empty -- ([a-z]|[A-Z]|_) --> word
    equality -- whitespace --> empty
    equality -- ([a-z]|[A-Z]|_) --> word
    equality -- [0-9] --> number
    equality -- ( --> parenthesis
    equality -- the other --> error
    parenthesis -- 

```
