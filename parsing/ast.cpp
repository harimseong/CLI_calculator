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
    std::cout << node->id_ << ": type=" << static_cast<int>(node->type_) << ", data=" << node->data_ << '\n';
    for (auto& child: node->nodes_) {
      child.id_ = ++count;
      std::cout << "-> ";
      std::cout << child.id_ << ": type=" << static_cast<int>(child.type_) << ", data=" << child.data_ << '\n';
      ast_queue.push(&child);
    }
    std::cout << "\n";
    if (--layer_size == 0) {
      layer_size = ast_queue.size();
    }
  }
}

} // parsing
