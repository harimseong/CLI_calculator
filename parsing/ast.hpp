#ifndef AST_HPP
#define AST_HPP

#include <string>
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
    unary_exp,
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
  ast&  operator=(const ast& node);

  void  set_type(type type);
  type  get_type(void) const;

  void              set_data(std::string_view data);
  std::string_view  get_data(void) const;

  void  insert(ast node);
  void  traverse(void);
private:
  std::string_view type_string(type t);

private:
  size_t            id_ = 0;
  type              type_;
  std::string       data_; // NOTE: string_view compile error?
  std::vector<ast>  nodes_;
};

} // parsing
#endif // AST_HPP
