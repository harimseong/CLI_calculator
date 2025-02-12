#include <stack>

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
enum class e_type {
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

e_state
fsm(std::string_view::iterator& itr)
{
  // TODO: maximum much scanner
  // (stores position of failure and use it to handle failure efficiently)
  static std::stack<e_state> stack;
  e_state state = e_state::incomplete;
  e_type  type;

  while (state != e_state::error) {
    type = get_char_type(*itr++);
    state = get_next_state(state, type);
    if (is_accepted(state)) {
      stack.clear();
    }
    stack.push(state);
  }
  while (stack.size() > 0 && !is_accepted(state) && state != e_state::error) {
    state = stack.pop();
    --itr;
  }
  if (is_accepted(state)) {
    return state;
  } else {
    return e_state::error;
  }
}

std::string_view
parsing::tokenizer::find_token(std::string_view input) const
{
  std::string_view::iterator begin;
  std::string_view::iterator end;

  while (true) {
    state  cur_state;

    begin = input.begin();
    end = begin;
    cur_state = fsm(end);
    switch (cur_state) {
      // NOTE: handle whitespaces in different loop?
      case state::whitespaces:
        input = input.substr(end - begin, input.npos);
        break;
      case state::operators: /* fall-through */
      case state::parenthesis: /* fall-through */
      case state::zero: /* fall-through */
      case state::nonzero_digits: /* fall-through */
      case state::floating: /* fall-through */
      case state::word:
        return std::string_view(input.data(), end - begin);
      case state::start: /* fall-through */
      case state::error:
        return std::string_view();
    }
  }
  return std::string_view{};
}
