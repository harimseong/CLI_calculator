#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string_view>

#include "token.hpp"

namespace parsing
{
class   tokenizer
{
public:
  tokenizer();
  ~tokenizer();
private:
  tokenizer(const tokenizer&);
  tokenizer	&operator=(const tokenizer&);

public:
  token get(std::string_view& input);
  token peek(std::string_view input) const;
  void  consume(std::string_view& input);
};

}

#endif // TOKENIZER_HPP
