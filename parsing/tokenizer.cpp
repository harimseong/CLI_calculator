#include "tokenizer.hpp"

namespace parsing
{

// constructors & destructor
tokenizer::tokenizer()
{
}

tokenizer::~tokenizer()
{
}

tokenizer::tokenizer(const tokenizer& t)
{
  (void)t;
}

// operators
tokenizer&
tokenizer::operator=(const tokenizer& t)
{
  (void)t;
  return *this;
}

token
tokenizer::get(std::string_view& input)
{
  (void)input;
  return token();
}

token
tokenizer::peek(std::string_view input) const
{
  (void)input;
  return token();
}

void
tokenizer::consume(std::string_view& input)
{
  (void)input;
}

}
