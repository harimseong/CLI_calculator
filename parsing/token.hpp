#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

namespace 
{

class  token
{
public:
  enum class type {
    EMPTY = 0,

    EQUAL = 0x100,

    PARENTHESIS = 0x200,

    OPERATOR = 0x300,
    UNARY_OP = 0x310,
    ADD_OP = 0x310,
    MUL_OP = 0x320,

    FUNCTION = 0x400,

    NUMBER = 0x500,
    FLOAT,
    INTEGER,

    WORD = 0x600,
  };
// constructors & destructor
  token() {};
  ~token() {};
  token(const token&);

// operators
  token	&operator=(const token&);

// member functions
  std::string data_;
  type        type_;
};

}

#endif // TOKEN_HPP
