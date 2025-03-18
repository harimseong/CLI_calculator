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

  token find_token(std::string_view input) const;
public:
  token get(std::string_view& input);
  token peek(std::string_view input) const;
  void  consume(std::string_view& input);

  token test_find_token(void) const;
};

}

#endif // TOKENIZER_HPP
