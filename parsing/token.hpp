#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <cstdint>
#include <string>
#include <string_view>

namespace parsing
{
class  token
{
public:
  typedef uint32_t type_pack;
  typedef enum type {
    invalid = 0x000,
    whitespace = 0x001,
    init = 0x002,

    equal = 0x100,

    parenthesis = 0x200,

    op = 0x300,
    unary_op = 0x301,
    add_op = 0x302,
    mul_op = 0x304,

    function = 0x400,

    number = 0x500,
    zero = 0x501,
    integer = 0x502,
    floating = 0x504,

    word = 0x600,

    eol = 0x700,

    mask = 0xff,
  } type;

  token()
  {
    type_pack_ = type::invalid;
  };

  token(std::string_view token, token::type_pack token_type = type::invalid)
  : data_{token},
    type_pack_{token_type}
  {};

  ~token() {};
  token(const token& t)
  {
    *this = t;
  };

  token	&operator=(const token& t)
  {
    data_ = t.data_;
    type_pack_ = t.type_pack_;
    return *this;
  };

  bool  comp_type(type_pack arg)
  {
    uint32_t  operand0 = type_pack_;
    uint32_t  operand1 = arg;

    if ((operand0 & ~type::mask) != (operand1 & ~type::mask)) {
      return false;
    }
    if ((operand1 & type::mask) == 0) {
      return true;
    }
    return (operand0 & type::mask) & (operand1 & type::mask);
  };

  std::string&  get_data(void)
  {
    return data_;
  };

  std::string data_;
  type_pack   type_pack_;
};

}

#endif // TOKEN_HPP
