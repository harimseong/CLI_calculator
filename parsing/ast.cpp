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
  for (auto& child: nodes_) {
    child.traverse();
  }
  if (data_.size() > 0) {
    std::cout << data_ << ' ';
  }
  /* BFS
  std::queue<ast*>  ast_queue;
  ast*              node;
  size_t            layer_size = 1;

  ast_queue.push(this);
  while (ast_queue.size() != 0) {
    node = ast_queue.front();
    ast_queue.pop();
    for (auto& child: node->nodes_) {
      if (child.data_.size() > 0) {
        std::cout << child.data_ << " ";
      }
      ast_queue.push(&child);
    }
    if (--layer_size == 0) {
      layer_size = ast_queue.size();
      std::cout << "\n";
    }
  }
  */
}

} // parsing
