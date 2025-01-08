#include "tokenizer.hpp"

// constructors & destructor
tokenizer::tokenizer()
{
}

tokenizer::~tokenizer()
{
}

tokenizer::tokenizer(const tokenizer& tokenizer)
{
  (void)tokenizer;
}

// operators
tokenizer&
tokenizer::operator=(const tokenizer& tokenizer)
{
  (void)tokenizer;
  return *this;
}
