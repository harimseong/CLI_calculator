#include <vector>

#include "token.hpp"
#include "tokenizer.hpp"

enum class e_state {
  error,
  incomplete,
  whitespaces,
  operators,
  parenthesis,
  zero,
  nonzero_digits,
  floating,
  word,
};

enum class e_char_type {
  invalid,
  whitespace,
  paren,
  op,
  starting_zero,
  nonzero_digit,
  digit,
  dot,
  starting_char,
  character,
};

static e_state
fsm(std::string_view::iterator& itr)
{
  // TODO: maximum munch scanner
  // (stores position of failure and use it to handle failure efficiently)
  std::vector<e_state> stack{e_state::error};
  e_state     state = e_state::incomplete;
  e_char_type char_type;

  while (state != e_state::error) {
    char_type = get_char_type(*itr++);
    state = get_next_state(state, char_type);
    if (is_accepted(state)) {
      stack.clear();
    }
    stack.push_back(state);
  }
  while (!is_accepted(state) && state != e_state::error) {
    state = stack.back();
    stack.pop_back();
    --itr;
  }
  if (is_accepted(state)) {
    return state;
  } else {
    return e_state::error;
  }
}

parsing::token
parsing::tokenizer::find_token(std::string_view input) const
{
  std::string_view::iterator  begin;
  std::string_view::iterator  end;
  token::type        token_type;

  while (true) {
    e_state  cur_state;

    begin = input.begin();
    end = begin;
    cur_state = fsm(end);
    switch (cur_state) {
      // NOTE: handle whitespaces in different loop?
      case e_state::whitespaces:
        input = input.substr(end - begin, input.npos);
        continue;
      case e_state::operators: /* fall-through */
        token_type = token::type::op;
        break;
      case e_state::parenthesis: /* fall-through */
        token_type = token::type::parenthesis;
        break;
      case e_state::zero: /* fall-through */
        token_type = token::type::zero;
        break;
      case e_state::nonzero_digits: /* fall-through */
        token_type = token::type::nonzero_digit;
        break;
      case e_state::floating: /* fall-through */
        token_type = token::type::floating;
        break;
      case e_state::word:
        token_type = token::type::word;
        break;
      case e_state::incomplete: /* fall-through */
      case e_state::error:
        return token{};
    }
    return parsing::token{std::string_view(input.data(), end - begin), token_type};
  }
  return token{};
}
