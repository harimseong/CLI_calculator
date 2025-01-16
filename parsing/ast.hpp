#ifndef AST_HPP
#define AST_HPP

namespace parsing
{
enum class  ast_type {
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

class  ast
{
  typedef   void* data_type;
public:
// constructors & destructor
  ast();
  ~ast();
  ast(const ast&);

// operators
  ast	&operator=(const ast&);

// member functions
  void  set_type(ast_type type);
  void  insert(ast node);

  template <typename T>
  void  set_data(T data);

  void* data;
};

} // parsing
#endif // AST_HPP
