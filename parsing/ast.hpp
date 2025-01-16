#ifndef AST_HPP
#define AST_HPP

#include <string_view>

namespace parsing
{
class  ast
{
public:
  enum class  type {
    empty,
    input,
    equation,
    assignment,
    expression,
    additive_exp,
    multiple_exp,
    term,
    function,
    power,
    trigonometric,
    unary_op,
    additive_op,
    multiple_op,
    number,
    variable,
  };

// constructors & destructor
  ast();
  ~ast();
  ast(const ast& node);

// operators
  ast	&operator=(const ast& node);

// member functions
  void  set_type(type type);
  void  insert(ast node);
  void  set_data(std::string_view data);

  type              type_;
  std::string_view  data_;
};

} // parsing
#endif // AST_HPP
