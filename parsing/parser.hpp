#ifndef PARSER_HPP
#define PARSER_HPP

#include <string_view>

#include "tokenizer.hpp"

namespace parsing
{
class  ast;

class  parser
{
  typedef   std::string_view  input_type;
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
  bool    parse(input_type input, ast& tree);
  bool    parse_assignment(input_type input, ast& tree);
  bool    parse_equation(input_type input, ast& tree);
  bool    parse_expression(input_type input, ast& tree);
  bool    parse_additive_exp(input_type input, ast& tree);
  bool    parse_term(input_type input, ast& tree);
  bool    parse_number(input_type input, ast& tree);
  bool    parse_variable(input_type input, ast& tree);
  bool    parse_function(input_type input, ast& tree);

// member variables
  tokenizer tokenizer_;
};

} // parsing
#endif // PARSER_HPP
