#include "ast.hpp"

namespace parsing
{

// constructors & destructor
ast::ast()
{
}

ast::~ast()
{
}

ast::ast(const ast& arg)
{
  (void)arg;
}

// operators
ast&
ast::operator=(const ast& arg)
{
  (void)arg;
  return *this;
}

}
