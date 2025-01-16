#ifndef AST_HPP
#define AST_HPP

#include <string_view>
#include <vector>

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

  ast();
  ~ast();
  ast(const ast& node);

  ast	&operator=(const ast& node);

  void  set_type(type type);
  type  get_type(void) const;

  void              set_data(std::string_view data);
  std::string_view  get_data(void) const;

  void  insert(ast node);

private:
  type              type_;
  std::string_view  data_;
  std::vector<ast>  nodes_;
};

} // parsing
#endif // AST_HPP
