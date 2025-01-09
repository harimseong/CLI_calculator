#ifndef PARSER_HPP
#define PARSER_HPP

#include <string_view>

#include "tokenizer.hpp"

namespace parsing
{
class  ast;

class  parser
{
  enum class  type_ {
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
public:
// constructors & destructor
  parser();
  ~parser();
  parser(const parser&);

// operators
  parser	&operator=(const parser&);

// member functions
  bool    parse(std::string_view input, ast& tree);
  bool    parse_assignment(std::string_view input, ast& tree);
  bool    parse_equation(std::string_view input, ast& tree);
  bool    parse_expression(std::string_view input, ast& tree);
  bool    parse_additive_exp(std::string_view input, ast& tree);
  bool    parse_term(std::string_view input, ast& tree);
  bool    parse_number(std::string_view input, ast& tree);
  bool    parse_variable(std::string_view input, ast& tree);
  bool    parse_function(std::string_view input, ast& tree);

// member variables
  tokenizer tokenizer_;
};

} // parsing
#endif // PARSER_HPP
