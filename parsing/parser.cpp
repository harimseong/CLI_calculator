#include "parser.hpp"

// constructors & destructor
parser::parser()
{
}

parser::~parser()
{
}

parser::parser(const parser& parser)
{
  (void)parser;
}

// operators
parser&
parser::operator=(const parser& parser)
{
  (void)parser;
  return *this;
}
