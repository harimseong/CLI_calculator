#include <stack>

#include "tokenizer.hpp"

enum class state {
  start,
  whitespaces,
  operators,
  parenthesis,
  zero,
  nonzero_digits,
  floating,
  word,
  error,
};
enum class type {
  whitespace,
  paren,
  op,
  starting_zero,
  nonzero_digit,
  digit,
  dot,
  starting_char,
  character,
  invalid,
};

state
fsm(std::string_view::iterator& itr)
{
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
