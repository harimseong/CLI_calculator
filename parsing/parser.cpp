
#include "parser.hpp"
#include "ast.hpp"

#ifdef DEBUG_PARSER
#include <iostream>
#include <vector>
#include <cstdio>

static int  s_depth;
static std::vector<uint16_t>  s_spaces(65, 0x207C);

# define PRINT_SPACES \
  std::cout << reinterpret_cast<const char*>(s_spaces.data()) + 127 - 2 * s_depth;

# define DEBUG_PRINT(fmt, ...) \
  PRINT_SPACES;\
  printf(fmt, __VA_ARGS__) 

# define DEBUG_PARSE_BEGIN \
{\
  ++s_depth;\
}

# define DEBUG_PARSE_EXIT \
{\
  --s_depth;\
}

# define DEBUG_PARSE_SUCCESS(str) \
{\
  PRINT_SPACES;\
  std::cout << "[O]" << __func__ << ": \"" << str << "\"";\
  std::cout << '\n';\
}

# define DEBUG_PARSE_FAIL(str) \
{\
  PRINT_SPACES;\
  std::cout << "[X]" << __func__ << ": \"" << str << "\"";\
  std::cout << '\n';\
}

#else
# define DEBUG_PRINT(fmt, ...)
# define DEBUG_PARSE_BEGIN
# define DEBUG_PARSE_EXIT
# define DEBUG_PARSE_SUCCESS(str) (void)str;
# define DEBUG_PARSE_FAIL(str) (void)str;
# define PRINT_SPACES
#endif

#define PARSE_BEGIN \
  const std::string_view old_input_ = input;\
  (void)old_input_;\
  DEBUG_PARSE_BEGIN;

#define PARSE_EXIT \
  DEBUG_PARSE_EXIT;

#define PARSE_FAIL(str) \
  DEBUG_PARSE_FAIL(str);\
  PARSE_EXIT;\
  input = old_input_;\
  return false;

#define PARSE_SUCCESS(str) \
  DEBUG_PARSE_SUCCESS(str);\
  PARSE_EXIT;\
  return true;


namespace parsing
{

// constructors & destructor
parser::parser()
{
}

parser::~parser()
{
}

// input           : LINEBREAK
//                 | expression LINEBREAK
bool
parser::parse(std::string_view& input, ast& node)
{
#ifdef DEBUG_PARSER
  s_spaces.back() = 0;
  if (1) {
    std::cout << "tokenizer test\n";
    tokenizer_.test_find_token();
    std::cout << '\n';
  }
#endif

  // LINEBREAK
  if (test_terminal(input, token_type::eol) == true) {
    return true;
  }

  // expression LINEBREAK
  if (parse_expression(input, node) == false) {
    return false;
  }
  if (test_terminal(input, token_type::eol) == false) {
    return false;
  }
  return true;
}

// expression      : equation    
//                 | simple_exp
bool
parser::parse_expression(std::string_view& input, ast& node)
{
  std::string::size_type  equal_pos;

  equal_pos = input.find('=');
  // simple_exp
  if (equal_pos == std::string::npos) {
    return parse_simple_exp(input, node);
  }
  // equation
  if (equal_pos == input.rfind('=')) {
    return parse_equation(input, node);
  }
  return false;
}

// equation        : VARIABLE '=' expression
//                 | expression '=' expression
bool
parser::parse_equation(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  ast       node1;
  ast_type  node1_type;
  ast       node2;

  if (parse_expression(input, node1) == false) {
    PARSE_FAIL(node.get_data());
  }
  node1_type = node1.get_type();
  if (tokenizer_.get(input).data_ != "="
    || parse_expression(input, node2) != true) {
    PARSE_FAIL(node.get_data());
  }
  node.set_type(node1_type == ast_type::variable ?
    ast_type::assignment : ast_type::equation);
  node.insert(node1);
  node.insert(node2);
  PARSE_SUCCESS(node.get_data());
}

// simple_exp      : additive_exp
bool
parser::parse_simple_exp(std::string_view& input, ast& node)
{
  // additive_exp
  return parse_additive_exp(input, node);
}

// additive_exp    : multiple_exp ADDITIVE_OP additive_exp
//                 | multiple_exp
bool
parser::parse_additive_exp(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  token op;
  ast   node1;
  ast   node2;

  if (parse_multiple_exp(input, node1) == false) {
    PARSE_FAIL(node.get_data());
  }
  if (test_terminal(input, token_type::add_op) == false) {
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  if (parse_additive_exp(input, node2) == false) {
    PARSE_FAIL(node.get_data());
  }
  node.set_type(ast_type::additive_exp);
  node.set_data(terminal_.data_);
  node.insert(node1);
  node.insert(node2);
  PARSE_SUCCESS(node.get_data());
}

// multiple_exp    : power MULTIPLE_OP multiple_exp
//                 | power 
bool
parser::parse_multiple_exp(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  ast   node1;
  ast   node2;

  if (parse_power(input, node1) == false) {
    PARSE_FAIL(node.get_data());
  }
  if (test_terminal(input, token_type::mul_op) == false) {
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  if (parse_multiple_exp(input, node2) == false) {
    PARSE_FAIL(node.get_data());
  }
  node.set_type(ast_type::multiple_exp);
  node.set_data(terminal_.data_);
  node.insert(node1);
  node.insert(node2);
  PARSE_SUCCESS(node.get_data());
}

// power           : unary_exp '^' power
//                 | unary_exp
bool
parser::parse_power(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  ast   node1;
  ast   node2;

  if (parse_unary_exp(input, node1) == false) {
    PARSE_FAIL(node.get_data());
  }
  if (tokenizer_.peek(input).data_ != "^") {
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  if (parse_power(input, node2) == false) {
    PARSE_FAIL(node.get_data());
  }
  node.set_type(ast_type::power);
  node.set_data(terminal_.data_);
  node.insert(node1);
  node.insert(node2);
  PARSE_SUCCESS(node.get_data());
}

// unary_exp       : UNARY_OP term
//                 | term
bool
parser::parse_unary_exp(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  ast   node1;
  bool  is_unary;

  is_unary = test_terminal(input, token_type::unary_op);
  if (parse_term(input, node1) == false) {
    PARSE_FAIL(node.get_data());
  }
  if (is_unary == false) {
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  node.set_type(ast_type::unary_exp);
  node.set_data(terminal_.data_);
  node.insert(node1);
  PARSE_SUCCESS(node.get_data());
}

// term            : '(' expression ')'
//                 | NUMBER
//                 | VARIABLE
//                 | function
bool
parser::parse_term(std::string_view& input, ast& node)
{
  PARSE_BEGIN;
  token tok;
  ast   node1;

  tok = tokenizer_.peek(input);
  if (tok.data_ == "(") {
    std::string_view::size_type pos;

    pos = input.rfind(')');
    if (pos == std::string_view::npos) {
      PARSE_FAIL(node.get_data());
    }
    input = input.substr(0, pos);
    if (parse_expression(input, node1) == false) {
      PARSE_FAIL(node.get_data());
    }
    tok = tokenizer_.peek(input);
    if (tok.data_ != ")") {
      PARSE_FAIL(node.get_data());
    }
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  if (test_terminal(input, token_type::number) == true) {
    node.set_type(ast_type::number);
    node.set_data(terminal_.data_);
    PARSE_SUCCESS(node.get_data());
  }
  if (test_terminal(input, token_type::word) == true) {
    node.set_type(ast_type::variable);
    node.set_data(terminal_.data_);
    PARSE_SUCCESS(node.get_data());
  }
  if (parse_function(input, node1) == true) {
    node = node1;
    PARSE_SUCCESS(node.get_data());
  }
  PARSE_FAIL(node.get_data());
}

bool
parser::parse_function(std::string_view& input, ast& node)
{
  // PARSE_BEGIN;
  (void)input;
  (void)node;
  return parse_trigonometric(input, node);
}

bool
parser::parse_trigonometric(std::string_view& input, ast& node)
{
  // PARSE_BEGIN;
  // PARSE_FAIL;
  (void)input;
  (void)node;
  return false;
}
bool
parser::test_terminal(std::string_view& input, token_type type)
{
  PARSE_BEGIN;
  token tok;

  tok = tokenizer_.peek(input);
  if (tok.comp_type(type) == false) {
    DEBUG_PRINT("token data=%s, type=%d\n", tok.data_.data(), tok.type_pack_);
    PARSE_FAIL(input);
  }
  terminal_ = tok;
  tokenizer_.consume(input);
  PARSE_SUCCESS(tok.data_);
}

} // parsing
