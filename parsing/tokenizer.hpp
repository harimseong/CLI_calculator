#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string_view>

#include "token.hpp"

namespace parsing
{
class   tokenizer
{
public:
  tokenizer() {};
  ~tokenizer() {};
private:
  tokenizer(const tokenizer&) = delete;
  tokenizer	&operator=(const tokenizer&) = delete;

  token find_token(std::string_view input);
public:
  token get(std::string_view& input);
  token peek(std::string_view input);
  void  consume(std::string_view& input);

  void  test_find_token(void);
};

}

#endif // TOKENIZER_HPP
