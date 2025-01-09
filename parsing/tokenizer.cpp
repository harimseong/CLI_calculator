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

tokenizer::tokenizer(const tokenizer& arg)
{
  (void)arg;
}

// operators
tokenizer&
tokenizer::operator=(const tokenizer& arg)
{
  (void)arg;
  return *this;
}

}
