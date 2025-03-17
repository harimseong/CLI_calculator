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
 * @return a token and update input.
 */
token
tokenizer::get(std::string_view& input)
{
  token new_token = peek(input);
  size_t token_size = new_token.data_.size();
  input = input.substr(token_size, input.size() - token_size);
  return new_token;
}

/*
 * @return a token from input.
 * input is copied so that original input will not be changed.
 */
token
tokenizer::peek(std::string_view input) const
{
  token found_token = find_token(input);;
  return found_token; 
}

/*
 * discard a token and update input.
 */
void
tokenizer::consume(std::string_view& input)
{
  (void)get(input);
}

} // parsing
