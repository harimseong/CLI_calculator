#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string_view>

#include "token.hpp"

namespace parsing
{
class   tokenizer
{
public:
  tokenizer(): cur_token_{"", token::init} {};
  ~tokenizer() {};
  tokenizer(const tokenizer&) = delete;
  tokenizer	&operator=(const tokenizer&) = delete;
public:
  token get(std::string_view& input);
  token peek(std::string_view& input);
  void  consume(std::string_view& input);

  static void  test_find_token(void);

private:
  token find_token(std::string_view input);

  token cur_token_;
};

}

#endif // TOKENIZER_HPP
