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

ast::ast(const ast& node)
{
  *this = node;
}

// operators
ast&
ast::operator=(const ast& node)
{
  type_ = node.type_;
  data_ = node.data_;
  return *this;
}

void
ast::set_type(ast::type type)
{
  (void)type;
}

void
ast::insert(ast node)
{
  (void)node;
}

void
ast::set_data(std::string_view data)
{
  (void)data;
}


} // parsing
