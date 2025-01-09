#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

namespace parsing
{
class  tokenizer
{
public:
  enum type {
    EMPTY,
    EQUAL,
    PARENTHESIS,
    UNARY_OP,
    ADD_OP,
    MUL_OP,
    FUNCTION,
    FLOAT,
    INTEGER,
    WORD,
  };
// constructors & destructor
  tokenizer();
  ~tokenizer();
  tokenizer(const tokenizer&);

// operators
  tokenizer	&operator=(const tokenizer&);

// member functions
};

}

#endif // TOKENIZER_HPP
