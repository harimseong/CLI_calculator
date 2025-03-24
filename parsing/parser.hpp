#ifndef PARSER_HPP
#define PARSER_HPP

#include <string_view>

#include "tokenizer.hpp"
#include "ast.hpp"

namespace parsing
{
class  parser
{
  typedef   token::type       token_type;
  typedef   ast::type         ast_type;
  typedef   bool              parsing_function_type(std::string_view&, ast&);
public:
  parser();
  ~parser();
  parser(const parser&) = delete;

  parser	&operator=(const parser&) = delete;

  parsing_function_type parse;
  parsing_function_type parse_assignment;
  parsing_function_type parse_equation;
  parsing_function_type parse_expression;
  parsing_function_type parse_unary_exp;
  parsing_function_type parse_additive_exp;
  parsing_function_type parse_multiple_exp;
  parsing_function_type parse_power;
  parsing_function_type parse_term;
  parsing_function_type parse_function;
  parsing_function_type parse_trigonometric;
  parsing_function_type parse_number;
  parsing_function_type parse_variable;
  parsing_function_type parse_unary_op;
  parsing_function_type parse_additive_op;
  parsing_function_type parse_multiple_op;
  parsing_function_type parse_linebreak;

private:
  void    print_string(std::string_view function, std::string_view str);
  void    print_node(std::string_view function, const ast& tree);

  tokenizer tokenizer_;
};

} // parsing
#endif // PARSER_HPP
