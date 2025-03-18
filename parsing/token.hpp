#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <string_view>

namespace parsing
{
class  token
{
public:
  enum class type {
    equal = 0x10,

    parenthesis = 0x20,

    op = 0x30,
    unary_op = 0x31,
    add_op = 0x32,
    mul_op = 0x33,

    function = 0x40,

    number = 0x50,
    zero = 0x51,
    nonzero_digit = 0x52,
    floating = 0x53,

    word = 0x60,

    invalid = 0x70,
    eol = 0x80
  };

  token()
  {
    type_ = type::invalid;
  };

  token(std::string_view token, token::type token_type = type::invalid)
  : data_{token},
    type_{token_type}
  {};

  ~token() {};
  token(const token& t)
  {
    *this = t;
  };

  token	&operator=(const token& t)
  {
    data_ = t.data_;
    type_ = t.type_;
    return *this;
  };

  bool  comp_type(type arg)
  {
    uint8_t operand0 = static_cast<uint8_t>(type_);
    uint8_t operand1 = static_cast<uint8_t>(arg);

    if ((operand1 & 0xf) == 0)
    {
      return (operand0 & ~0xf) == (operand1 & ~0xf);
    }
    return type_ == arg;
  };


  std::string data_;
  type        type_;
};

}

#endif // TOKEN_HPP
