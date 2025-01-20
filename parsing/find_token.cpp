#include "tokenizer.hpp"

namespace parsing
{
enum class type {
  whitespace,
  parenthesis,
  operators,
  starting_zero,
  nonzero_digit,
  digit,
  dot,
  starting_char,
  character,
  invalid,
};

void
fsm(std::string_view::iterator& itr)
{

}

std::string_view
tokenizer::find_token(std::string_view input) const
{
  std::string_view::iterator begin;
  std::string_view::iterator end;

  while (true) {
    begin = input.begin();
    end = begin;

    fsm(end);
  }
  return input.substr(0, end - begin);
}

} // parsing
