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
  typedef   bool              nonterminal_parser_t(std::string_view&, ast&);
public:
  parser();
  ~parser();
  parser(const parser&) = delete;

  parser	&operator=(const parser&) = delete;

  nonterminal_parser_t  parse;
  nonterminal_parser_t  parse_expression;
  nonterminal_parser_t  parse_equation;
  nonterminal_parser_t  parse_simple_exp;
  nonterminal_parser_t  parse_additive_exp;
  nonterminal_parser_t  parse_multiple_exp;
  nonterminal_parser_t  parse_power;
  nonterminal_parser_t  parse_unary_exp;
  nonterminal_parser_t  parse_term;
  nonterminal_parser_t  parse_function;
  nonterminal_parser_t  parse_trigonometric;

private:
  bool    test_terminal(std::string_view& input, token_type type);
  bool    test_terminal(std::string_view& input, std::string_view data);

  void    print_string(std::string_view function, std::string_view str);
  void    print_node(std::string_view function, const ast& tree);

  tokenizer tokenizer_;
  token     terminal_;
};

} // parsing
#endif // PARSER_HPP
