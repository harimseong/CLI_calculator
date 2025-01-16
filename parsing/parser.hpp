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
public:
  parser();
  ~parser();
  parser(const parser&);

  parser	&operator=(const parser&);

  bool    parse(std::string_view input, ast& tree);
  bool    parse_assignment(std::string_view input, ast& tree);
  bool    parse_equation(std::string_view input, ast& tree);
  bool    parse_expression(std::string_view input, ast& tree);
  bool    parse_additive_exp(std::string_view input, ast& tree);
  bool    parse_multiple_exp(std::string_view input, ast& tree);
  bool    parse_power(std::string_view input, ast& tree);
  bool    parse_term(std::string_view input, ast& tree);
  bool    parse_function(std::string_view input, ast& tree);
  bool    parse_trigonometric(std::string_view input, ast& tree);
  bool    parse_number(std::string_view input, ast& tree);
  bool    parse_variable(std::string_view input, ast& tree);
  bool    parse_unary_op(std::string_view input, ast& tree);
  bool    parse_additive_op(std::string_view input, ast& tree);
  bool    parse_multiple_op(std::string_view input, ast& tree);
  bool    parse_linebreak(std::string_view input, ast& tree);

private:
  tokenizer tokenizer_;
};

} // parsing
#endif // PARSER_HPP
