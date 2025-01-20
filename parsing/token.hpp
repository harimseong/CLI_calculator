#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string_view>

namespace parsing
{
class  token
{
public:
  enum class type {
    equal = 0x100,

    parenthesis = 0x200,

    op = 0x300,
    unary_op = 0x310,
    add_op = 0x310,
    mul_op = 0x320,

    function = 0x400,

    number = 0x500,
    digit = 0x510,
    zero = 0x511,
    nonzero_digit = 0x512,
    floating,

    word = 0x600,

    invalid = 0x700,
  };
// constructors & destructor
  token()
  {
    type_ = type::invalid;
  };
  token(std::string_view t)
  : data_{t}
  {
    type_ = type::invalid;
  };
  ~token() {};
  token(const token& t)
  {
    *this = t;
  };

// operators
  token	&operator=(const token& t)
  {
    data_ = t.data_;
    type_ = t.type_;
    return *this;
  };

// member functions
  std::string_view  data_;
  type              type_;
};

}

#endif // TOKEN_HPP
