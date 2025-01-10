#include <cassert>

#include "parser.hpp"

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
parser::parse(input_type input, ast& tree)
{
  tree.set_type(type_::input);
  if (parse_linebreak(input, tree) == true) {
    goto pass0;
  }
  return true;
pass0:
  ast   node0;
  bool  ret0 = parse_equation(input, node0)
  || parse_assignment(input, node0)
  || parse_expression(input, node0);
  if (ret0 == true) {
    goto pass1;
  }
  return false;
pass1:
  if (parse_linebreak(input, tree) == true) {
    goto pass2;
  }
  return false;
pass2:
  tree.insert(node0);
  return true;
}

bool
parser::parse_equation(input_type input, ast& tree)
{
  tree.set_type(type_::equation);
  // early return
  if (input.find('=') == input_type::npos) {
    return false;
  }

  ast   node0;
  ast   node1;
  bool  ret;

  ret = parse_expression(input, node0) == false;
  if (ret == true) {
    goto pass0;
  }
  return false;
pass0:
  if (tokenizer_.get(input).data != '=') {
    assert(__FUNCTION__);
  }
  ret = parse_expression(input, node1);
  if (ret == true) {
    goto pass1;
  }
  return false;
pass1:
  tree.insert(node0);
  tree.insert(node1);
  return true;
}

bool
parser::parse_assignment(input_type input, ast& tree)
{
  tree.set_type(type_::assignment);
  // early return
  if (input.find('=') == input_type::npos) {
    return false;
  }
  // will be implemented in v2
  return false;
}

bool
parser::parse_expression(input_type input, ast& tree)
{
//tree.set_type(type_::expression);
  bool ret = parse_term(input, tree)
  || parse_additive_exp(input, tree);
  return ret;
}

bool
parser::parse_term(input_type input, ast& tree)
{
  tree.set_type(type_::term);
  if (tokenizer_.peek(input).data == '(') {
    tokenizer_.consume(input);

    ast   node0;
    bool  ret0;

    ret0 = parse_term(input, node0);
    if (ret0 == true) {
      goto pass0;
    }

    if (parse_unary_op(input) == true) {
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
    if (tokenizer_.get(input).data != ')') {
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
parser::parse_additive_exp(input_type input, ast& tree)
{
  tree.set_type(type_::additive_exp);
  ast   node0;
  bool  ret0;

  ret0 = parse_multiple_exp(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  if (parse_additive_op(input) == true) {
    goto pass1;
  }
  tree.insert(node0);
  return true;
pass1:
  ast   node1;
  bool  ret1;

  ret1 = parse_additive_exp(input, node1);
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
parser::parse_multiple_exp(input_type input, ast& tree)
{
  tree.set_type(type_::multiple_exp);
  ast   node0;
  bool  ret0;

  ret0 = parse_term(input, node0);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  if (parse_multiple_op(input) == true) {
    goto pass1;
  }
  tree.insert(node0);
  return true;
pass1:
  ast   node1;
  bool  ret1;

  ret1 = parse_multiple_exp(input, node1);
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
parser::parse_function(input_type input, ast& tree)
{
  bool  ret = parse_power(input, tree)
    || parse_trigonometric(input, tree);
  return ret;
}

bool
parser::parse_power(input_type input, ast& tree)
{
  tree.set_type(type_::power);
  ast   node0;
  bool  ret0;

  ret0 = parse_term(input, tree);
  if (ret0 == true) {
    goto pass0;
  }
  return false;
pass0:
  if (tokenizer_.peek().data == '^') {
    tokenizer_.consume();
    goto pass1;
  }
  return false;
pass1:
  ast   node1;
  bool  ret1;

  ret1 = parse_term(input, tree);
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
parser::parse_trigonometric(input_type input, ast& tree)
{
  // v2
  return false;
}

bool
parser::parse_unary_op(input_type input)
{
}

bool
parser::parse_additive_op(input_type input)
{
}

bool
parser::parse_multiple_op(input_type input)
{
}

bool
parser::parse_number(input_type input, ast& tree)
{
}

bool
parser::parse_variable(input_type input, ast& tree)
{
}

bool
parser::parse_linebreak(input_type input, ast& tree)
{
}

} // parsing
