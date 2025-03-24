#include <queue>
#include <iostream>

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

ast&
ast::operator=(const ast& node)
{
  type_ = node.type_;
  data_ = node.data_;
  if (node.nodes_.size() > 0) {
    nodes_ = node.nodes_;
  }
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

void
ast::traverse(void)
{
  std::queue<ast*>  ast_queue;
  ast*              node;
  size_t            layer_size = 1;
  size_t            count = 0;

  ast_queue.push(this);
  while (ast_queue.size() != 0) {
    node = ast_queue.front();
    ast_queue.pop();
    if (node->nodes_.size() == 0) {
      std::cout << "terminal\n";
    }
    std::cout << node->id_ << ": [" << type_string(node->type_) << ", \"" << node->data_ << "\"]\n";
    for (auto& child: node->nodes_) {
      child.id_ = ++count;
      std::cout << "-> ";
      std::cout << node->id_ << ": [" << type_string(child.type_) << ", \"" << child.data_ << "\"]\n";
      ast_queue.push(&child);
    }
    std::cout << "\n";
    if (--layer_size == 0) {
      layer_size = ast_queue.size();
    }
  }
}

std::string_view
ast::type_string(type t)
{
  static const std::string  type_strings[] = {
    "empty",
    "input",
    "equation",
    "assignment",
    "expression",
    "unary_exp",
    "additive_exp",
    "multiple_exp",
    "term",
    "function",
    "power",
    "trigonometric",
    "unary_op",
    "additive_op",
    "multiple_op",
    "number",
    "variable",
  };

  switch (t) {
    case type::empty:
      return type_strings[0];
    case type::input:
      return type_strings[1];
    case type::equation:
      return type_strings[2];
    case type::assignment:
      return type_strings[3];
    case type::expression:
      return type_strings[4];
    case type::unary_exp:
      return type_strings[5];
    case type::additive_exp:
      return type_strings[6];
    case type::multiple_exp:
      return type_strings[7];
    case type::term:
      return type_strings[8];
    case type::function:
      return type_strings[9];
    case type::power:
      return type_strings[10];
    case type::trigonometric:
      return type_strings[11];
    case type::unary_op:
      return type_strings[12];
    case type::additive_op:
      return type_strings[13];
    case type::multiple_op:
      return type_strings[14];
    case type::number:
      return type_strings[15];
    case type::variable:
      return type_strings[16];
  };
  return "error";
}

} // parsing
