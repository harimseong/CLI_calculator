#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <string_view>

#include "token.hpp"

namespace parsing
{
class   tokenizer
{
public:

  // == operator overloading?
// constructors & destructor
  tokenizer();
  ~tokenizer();
  tokenizer(const tokenizer&);

// operators
  tokenizer	&operator=(const tokenizer&);

// member functions
  token get(std::string_view& input) {return token();};
  token peek(std::string_view input) {return token();} const;
  void  consume(std::string_view& input) {};
};

}

#endif // TOKENIZER_HPP
