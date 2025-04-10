#include <vector>

#include "token.hpp"
#include "tokenizer.hpp"

enum class e_state {
  error,
  start,
  whitespaces,
  minus,
  operators,
  parenthesis,
  zero,
  nonzero_digits,
  floating,
  word,
};

enum class e_char {
  invalid,
  whitespace,
  parenthesis,
  minus,
  operators,
  zero,
  nonzero_digit,
  dot,
  word_starter, 
  character,
};

#include "char_table.hpp"

static e_state
get_next_state(e_state state, e_char char_type)
{
  switch (state) {
    case e_state::error:
      return state;

    case e_state::start:
      switch (char_type) {
        case e_char::whitespace:
          return e_state::whitespaces;

        case e_char::minus:
          return e_state::minus;

        case e_char::operators:
          return e_state::operators;

        case e_char::parenthesis:
          return e_state::parenthesis;

        case e_char::zero:
          return e_state::zero;

        case e_char::nonzero_digit:
          return e_state::nonzero_digits;

        case e_char::word_starter:
          return e_state::word;

        default:
          return e_state::error;
      };

    case e_state::whitespaces:
      if (char_type == e_char::whitespace) {
        return state;
      }
      return e_state::error;

    case e_state::minus:
    case e_state::operators:
      return e_state::error;

    case e_state::parenthesis:
      return e_state::error;

    case e_state::zero:
      if (char_type == e_char::dot) {
        return e_state::floating;
      }
      return e_state::error;

    case e_state::nonzero_digits:
      switch (char_type) {
        case e_char::dot:
          return e_state::floating;
        case e_char::zero:
        case e_char::nonzero_digit:
          return e_state::nonzero_digits;
        default:
          return e_state::error;
      };

    case e_state::floating:
      if (char_type == e_char::nonzero_digit
          || char_type == e_char::zero) {
        return e_state::floating;
      }
      return e_state::error;

    case e_state::word:
      if (char_type == e_char::word_starter
          || char_type == e_char::zero
          || char_type == e_char::nonzero_digit) {
        return e_state::word;
      }
      return e_state::error;
  };
  return e_state::error;
}

static bool
is_accepted(e_state state)
{
  switch (state) {
    case e_state::whitespaces:
    case e_state::minus:
    case e_state::operators:
    case e_state::parenthesis:
    case e_state::zero:
    case e_state::nonzero_digits:
    case e_state::floating:
    case e_state::word:
      return true;
    default:
      return false;
  }
}

static e_state
fsm(std::string_view::iterator& itr, const std::string_view::iterator end)
{
  // TODO: maximal munch scanner
  // TODO: stores position of failure and use it to handle failure efficiently
  std::vector<e_state> stack;
  e_state state = e_state::start;
  e_char  char_type;

  // NOTE: assumes null-terminated string
  while (itr != end && state != e_state::error) {
    char_type = char_table[static_cast<int>(*itr++)];
    state = get_next_state(state, char_type);
    if (is_accepted(state)) {
      stack.clear();
    }
    stack.push_back(state);
  }
  while (stack.size() > 0 && !is_accepted(state)) {
    stack.pop_back();
    state = stack.back();
    --itr;
  }
  if (is_accepted(state)) {
    return state;
  } else {
    return e_state::error;
  }
}

parsing::token
parsing::tokenizer::find_token(std::string_view input)
{
  std::string_view::iterator  begin;
  std::string_view::iterator  token_end;
  token::type_pack  token_type = token::type::invalid;
  e_state           cur_state;

  if (input.size() == 0) {
    return token{"", token::type::eol};
  }
  begin = input.begin();
  token_end = begin;
  cur_state = fsm(token_end, input.end());
  switch (cur_state) {
    // NOTE: handle whitespaces in different loop?
    case e_state::whitespaces:
      token_type |= token::type::whitespace;
      break;

    case e_state::minus: /* fall-through */
    case e_state::operators:
      token_type |= token::type::op;
      switch (input.front()) {
        case '+': /* fall-through */
        case '-':
          token_type |= token::type::add_op;
          token_type |= token::type::unary_op;
          break;
        case '*': /* fall-through */
        case '/':
          token_type |= token::type::mul_op;
          break;
        case '^':
          token_type |= token::type::op;
          break;
        default:
          token_type = token::type::invalid;
      };
      break;

    case e_state::parenthesis:
      token_type |= token::type::parenthesis;
      break;

    case e_state::zero:
      token_type |= token::type::zero;
      break;

    case e_state::nonzero_digits:
      token_type |= token::type::integer;
      break;

    case e_state::floating:
      token_type |= token::type::floating;
      break;

    case e_state::word:
      token_type |= token::type::word;
      break;

    case e_state::start: /* fall-through */
    case e_state::error:
      return token{"", token::type::invalid};
  }
  token new_token{std::string_view(input.data(), token_end - begin), token_type};
  return new_token;
}
