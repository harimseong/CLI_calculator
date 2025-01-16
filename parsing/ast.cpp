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
  type_ = type;
}

ast::type
ast::get_type(void) const
{
  return type_;
}

void
ast::insert(ast node)
{
  nodes_.push_back(node);
}

void
ast::set_data(std::string_view data)
{
  data_ = data;
}

std::string_view
ast::get_data(void) const
{
  return data_;
}

} // parsing
