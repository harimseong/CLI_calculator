#include "parser.hpp"

namespace parsing
{

// constructors & destructor
parser::parser()
{
}

parser::~parser()
{
}

parser::parser(const parser& arg)
{
  (void)arg;
}

// operators
parser&
parser::operator=(const parser& arg)
{
  (void)arg;
  return *this;
}

}
