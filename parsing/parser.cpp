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
parser::parse(std::string_view input, ast& tree)
{
  tree.set_type(type_::input);
  if (tokenizer_.peek(input).type == tokenizer::EMPTY) {
    return true;
  }
  ast   node;
  bool  ret = parse_equation(input, node)
  || parse_assignment(input, node)
  || parse_expression(input, node);
  if (ret == true) {
    goto pass;
  }
  return false;
pass:
  if (ret == false || tokenizer_.get(input).type != tokenizer::EMPTY) {
    return false;
  }
  tree.insert(node);
  return true;
}

bool
parser::parse_equation(std::string_view input, ast& tree)
{
  tree.set_type(type_::equation);
  // early return
  if (input.find('=') == std::string_view::npos) {
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
parser::parse_assignment(std::string_view input, ast& tree)
{
  tree.set_type(type_::assignment);
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
//tree.set_type(type_::expression);
  bool ret = parse_term(input, tree)
  || parse_additive_exp(input, tree);
  return ret;
}

bool
parser::parse_term(std::string_view input, ast& tree)
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
    if (tokenizer_.peek(input).type == tokenizer::UNARY_OP) {
      token t = tokenizer_.get(input);
      ast   node1;
      bool  ret1;

      ret1 = parse_term(input, node1);
      if (ret1 == true) {
        node0.set_type(type_::unary_op);
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
parser::parse_additive_exp(std::string_view input, ast& tree)
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
  if (tokenizer_.peek(input).type == tokenizer_::ADD_OP) {
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

} // parsing
