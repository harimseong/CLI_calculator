#include <iostream>
#include <cassert>

#include "parser.hpp"
#include "ast.hpp"

#define COMMON_START \
  ++depth;

#define COMMON_EXIT \
  --depth;
  
#define ERROR(input) \
  COMMON_EXIT; \
  std::cout << "E "; \
  for (int i = 1; i < depth; ++i) { std::cout << "| "; } \
  print_string(__func__, input); \
  std::cout << "\n";

#define SUCCESS(node) \
  COMMON_EXIT; \
  std::cout << "| "; \
  for (int i = 1; i < depth; ++i) { std::cout << "| "; } \
  input_orig = input; \
  print_node(__func__, node); \
  std::cout << "\n";

static int  depth;

namespace parsing
{

// constructors & destructor
parser::parser()
{
}

parser::~parser()
{
}

bool
parser::parse(std::string_view& input_orig, ast& tree)
{
  depth = 0;
  COMMON_START;
  tree.set_type(ast_type::input);

  std::string_view  input = input_orig;
  bool  ret0;
  ast   node0;

  ret0 = parse_linebreak(input, node0);
  if (ret0 == true) {
    tree.insert(node0);
    SUCCESS(tree);
    return true;
  }
  ret0 = parse_equation(input, node0)
  || parse_assignment(input, node0)
  || parse_expression(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_linebreak(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  ERROR(input);
  return false;
pass1:
  tree.insert(node0);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_equation(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::equation);
  std::string_view  input = input_orig;
  // early return
  if (input.find('=') == std::string_view::npos) {
    ERROR(input);
    return false;
  }
  bool  ret0;
  ast   node0;

  ret0 = parse_expression(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  assert(tokenizer_.get(input).data_ == "=");

  bool  ret1;
  ast   node1;
  ret1 = parse_expression(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  ERROR(input);
  return false;
pass1:
  tree.insert(node0);
  tree.insert(node1);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_assignment(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::assignment);
  std::string_view  input = input_orig;
  // early return
  if (input.find('=') == std::string_view::npos) {
    ERROR(input);
    return false;
  }
  // will be implemented in v2
  ERROR(input);
  return false;
}

bool
parser::parse_expression(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::expression);
  std::string_view  input = input_orig;
  bool ret = parse_unary_exp(input, tree);

  if (ret == false) {
    ERROR(input);
    return false;
  }
  SUCCESS(tree);
  return true;
}

bool
parser::parse_unary_exp(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::unary_exp);
  std::string_view  input = input_orig;
  bool  ret0;
  bool  ret1;
  ast   node0;
  ast   node1;

  ret0 = parse_unary_op(input, node0);
  ret1 = parse_additive_exp(input, node1);
  if (ret1 == true) {
    goto pass2;
  }
  ERROR(input);
  return false;
pass2:
  if (ret0 == true) {
    tree.insert(node1);
    tree.set_data(node0.get_data());
  } else {
    tree = node1;
  }
  SUCCESS(tree);
  return true;
}

bool
parser::parse_additive_exp(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::additive_exp);
  std::string_view  input = input_orig;
  bool  ret0;
  ast   node0;

  ret0 = parse_multiple_exp(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_additive_op(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  tree = node0;
  SUCCESS(tree);
  return true;
pass1:
  bool  ret2;
  ast   node2;

  ret2 = parse_additive_exp(input, node2);
  if (ret2 == true) {
    goto pass2;
  }
  ERROR(input);
  return false;
pass2:
  tree.insert(node0);
  tree.insert(node2);
  tree.set_data(node1.get_data());
  SUCCESS(tree);
  return true;
}

bool
parser::parse_multiple_exp(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::multiple_exp);
  std::string_view  input = input_orig;
  bool  ret0;
  ast   node0;

  ret0 = parse_power(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_multiple_op(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  tree = node0;
  SUCCESS(tree);
  return true;
pass1:
  bool  ret2;
  ast   node2;

  ret2 = parse_multiple_exp(input, node2); 
  if (ret2 == true) {
    goto pass2;
  }
  ERROR(input);
  return false;
pass2:
  tree.insert(node0);
  tree.insert(node2);
  tree.set_data(node1.get_data());
  SUCCESS(tree);
  return true;
}

bool
parser::parse_power(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::power);
  std::string_view  input = input_orig;
  bool  ret0;
  ast   node0;

  ret0 = parse_term(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  if (tokenizer_.peek(input).data_ == "^") {
    tokenizer_.consume(input);
    goto pass1;
  }
  tree = node0;
  SUCCESS(tree);
  return true;
pass1:
  bool  ret1;
  ast   node1;

  ret1 = parse_term(input, node1);
  if (ret1 == true) {
    goto pass2;
  }
  ERROR(input);
  return false;
pass2:
  tree.insert(node0);
  tree.insert(node1);
  SUCCESS(tree);
  return true;
}


bool
parser::parse_term(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::term);
  std::string_view  input = input_orig;
  if (tokenizer_.peek(input).data_ == "(") {
    tokenizer_.consume(input);
    bool  ret0;
    ast   node0;

    ret0 = parse_expression(input, node0);
    if (ret0 == true) {
      goto pass0;
    }

    ret0 = parse_term(input, node0);
    if (ret0 == true) {
      goto pass0;
    }
    
    ERROR(input);
    return false;
pass0:
    if (tokenizer_.get(input).data_ != ")") {
      ERROR(input);
      return false;
    }
    tree = node0;
    SUCCESS(tree);
    return true;
  }
  bool  ret2;
  ast   node2;

  ret2 = parse_number(input, node2);
  if (ret2 == true) {
    goto pass1;
  }
  ret2 = parse_variable(input, node2);
  if (ret2 == true) {
    goto pass1;
  }
  ret2 = parse_function(input, node2);
  if (ret2 == true) {
    goto pass1;
  }
  ERROR(input);
  return false;
pass1:
  tree = node2;
  SUCCESS(tree);
  return true;
}

bool
parser::parse_function(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::function);
  std::string_view  input = input_orig;
  bool  ret0;
  ast   node0;

  ret0 = parse_trigonometric(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  tree.insert(node0);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_trigonometric(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  (void)input_orig;
  (void)tree;
  ERROR(input_orig);
  return false; // v2
}

bool
parser::parse_number(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::number);
  std::string_view  input = input_orig;
  bool  ret0;

  ret0 = tokenizer_.peek(input).comp_type(token_type::number);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  tree.set_data(tokenizer_.get(input).data_);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_variable(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::variable);
  std::string_view  input = input_orig;
  bool  ret0;

  ret0 = tokenizer_.peek(input).comp_type(token_type::word);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  tree.set_data(tokenizer_.get(input).data_);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_unary_op(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::unary_op);
  std::string_view  input = input_orig;
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::unary_op);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  tree.set_data(token0.data_);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_additive_op(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::additive_op);
  std::string_view  input = input_orig;
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::add_op);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(token0.data_);
  return false;
pass0:
  tree.set_data(token0.data_);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_multiple_op(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::multiple_op);
  std::string_view  input = input_orig;
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::mul_op);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(token0.data_);
  return false;
pass0:
  tree.set_data(token0.data_);
  SUCCESS(tree);
  return true;
}

bool
parser::parse_linebreak(std::string_view& input_orig, ast& tree)
{
  COMMON_START;
  tree.set_type(ast_type::empty);
  std::string_view  input = input_orig;
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::eol);
  if (ret0 == true) {
    goto pass0;
  }
  ERROR(input);
  return false;
pass0:
  tree.set_data("");
  SUCCESS(tree);
  return true;
}

void
parser::print_string(std::string_view function, std::string_view str)
{
  std::cout << function << ": \"" << str << "\"";
}

void
parser::print_node(std::string_view function, const ast& tree)
{
  std::cout << function << ": data=\"" << tree.get_data()
    << "\" | type=" << static_cast<int>(tree.get_type());
}

} // parsing
