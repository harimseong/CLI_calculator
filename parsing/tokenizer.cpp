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

/*
 * @return first token of input and discard consumed characters from input.
 */
token
tokenizer::get(std::string_view& input)
{
  token t = peek(input);
  consume(input);
  return token();
}

/*
 * @return first token of input.
 */
token
tokenizer::peek(std::string_view input) const
{
  (void)input;
  return token();
}

/*
 * discard consumed characters from input as if a first token is taken.
 */
void
tokenizer::consume(std::string_view& input)
{
  (void)input;
}

} // parsing
