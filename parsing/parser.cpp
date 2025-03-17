#include <cassert>

#include "parser.hpp"
#include "ast.hpp"

namespace parsing
{

// constructors & destructor
parser::parser()
{
}

parser::~parser()
{
}

parser::parser(const parser& arg)
{
  (void)arg;
}

// operators
parser&
parser::operator=(const parser& arg)
{
  (void)arg;
  return *this;
}

bool
parser::parse(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::input);
  bool  ret0;
  ast   node0;

  ret0 = parse_linebreak(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return true;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_equation(input, node1)
  || parse_assignment(input, node1)
  || parse_expression(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  return false;
pass1:
  bool  ret2;
  ast   node2;

  ret2 = parse_linebreak(input, node2);
  if (ret2 == true) {
    goto pass2;
  }
  return false;
pass2:
  tree.insert(node1);
  return true;
}

bool
parser::parse_equation(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::equation);
  // early return
  if (input.find('=') == std::string_view::npos) {
    return false;
  }
  bool  ret0;
  ast   node0;

  ret0 = parse_expression(input, node0) == false;
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  assert(tokenizer_.get(input).data_ == "=");

  bool  ret1;
  ast   node1;
  ret1 = parse_expression(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  return false;
pass1:
  tree.insert(node0);
  tree.insert(node1);
  return true;
}

bool
parser::parse_assignment(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::assignment);
  // early return
  if (input.find('=') == std::string_view::npos) {
    return false;
  }
  // will be implemented in v2
  return false;
}

bool
parser::parse_expression(std::string_view input, ast& tree)
{
//tree.set_type(ast_type::expression);
  bool ret = parse_term(input, tree)
  || parse_additive_exp(input, tree);
  return ret;
}

bool
parser::parse_additive_exp(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::additive_exp);
  bool  ret0;
  ast   node0;

  ret0 = parse_multiple_exp(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_additive_op(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  tree = node0;
  return true;
pass1:
  bool  ret2;
  ast   node2;

  ret2 = parse_additive_exp(input, node2);
  if (ret2 == true) {
    goto pass2;
  }
  return false;
pass2:
  node1.insert(node0);
  node1.insert(node2);
  tree.insert(node1);
  return true;
}

bool
parser::parse_multiple_exp(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::multiple_exp);
  bool  ret0;
  ast   node0;

  ret0 = parse_power(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  bool  ret1;
  ast   node1;

  ret1 = parse_multiple_op(input, node1);
  if (ret1 == true) {
    goto pass1;
  }
  tree = node0;
  return true;
pass1:
  bool  ret2;
  ast   node2;

  ret2 = parse_multiple_exp(input, node2); 
  if (ret2 == true) {
    goto pass2;
  }
  return false;
pass2:
  node1.insert(node0);
  node1.insert(node2);
  tree.insert(node1);
  return true;
}

bool
parser::parse_power(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::power);
  bool  ret0;
  ast   node0;

  ret0 = parse_term(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  if (tokenizer_.peek(input).data_ == "^") {
    tokenizer_.consume(input);
    goto pass1;
  }
  tree = node0;
  return true;
pass1:
  bool  ret1;
  ast   node1;

  ret1 = parse_term(input, node1);
  if (ret1 == true) {
    goto pass2;
  }
  return false;
pass2:
  tree.insert(node0);
  tree.insert(node1);
  return true;
}


bool
parser::parse_term(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::term);
  if (tokenizer_.peek(input).data_ == "(") {
    tokenizer_.consume(input);
    bool  ret0;
    ast   node0;

    ret0 = parse_term(input, node0);
    if (ret0 == true) {
      goto pass0;
    }

    ret0 = parse_unary_op(input, node0);
    if (ret0 == true) {
      ast   node1;
      bool  ret1;

      ret1 = parse_term(input, node1);
      if (ret1 == true) {
        node0.insert(node1);
        goto pass0;
      }
      return false;
    }
    ret0 = parse_expression(input, node0);
    if (ret0 == true) {
      goto pass0;
    }
    return false;
pass0:
    if (tokenizer_.get(input).data_ != ")") {
      return false;
    }
    tree.insert(node0);
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
  return false;
pass1:
  tree.insert(node2);
  return true;
}

bool
parser::parse_function(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::function);
  bool  ret0;
  ast   node0;

  ret0 = parse_trigonometric(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.insert(node0);
  return true;
}

bool
parser::parse_trigonometric(std::string_view input, ast& tree)
{
  (void)input;
  (void)tree;
  return false; // v2
}

bool
parser::parse_number(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::number);
  bool  ret0;

  ret0 = tokenizer_.peek(input).comp_type(token_type::number);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data(tokenizer_.get(input).data_);
  return true;
}

bool
parser::parse_variable(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::variable);
  bool  ret0;

  ret0 = tokenizer_.peek(input).comp_type(token_type::word);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data(tokenizer_.get(input).data_);
  return true;
}

bool
parser::parse_unary_op(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::unary_op);
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::unary_op);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data(token0.data_);
  return true;
}

bool
parser::parse_additive_op(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::additive_op);
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::add_op);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data(token0.data_);
  return true;
}

bool
parser::parse_multiple_op(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::multiple_op);
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::mul_op);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data(token0.data_);
  return true;
}

bool
parser::parse_linebreak(std::string_view input, ast& tree)
{
  tree.set_type(ast_type::empty);
  bool  ret0;
  token token0;

  token0 = tokenizer_.get(input);
  ret0 = token0.comp_type(token_type::empty);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  tree.set_data("");
  return true;
}

} // parsing
