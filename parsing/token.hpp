#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string_view>

namespace 
{

class  token
{
public:
  enum class type {
    empty = 0,

    equal = 0X100,

    parenthesis = 0X200,

    op = 0X300,
    unary_op = 0X310,
    add_op = 0X310,
    mul_op = 0X320,

    function = 0X400,

    number = 0X500,
    floating,
    integer,

    word = 0X600,
  };
// constructors & destructor
  token() {};
  ~token() {};
  token(const token&);

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
