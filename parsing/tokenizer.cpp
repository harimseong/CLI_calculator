#include <vector>
#include <string>
#include <iostream>

#include "tokenizer.hpp"

namespace parsing
{

/*
 * @return a token and update input.
 */
token
tokenizer::get(std::string_view& input)
{
  token new_token = peek(input);
  size_t token_size = new_token.data_.size();
  input = input.substr(token_size, input.size() - token_size);
  return new_token;
}

/*
 * @return a token from input.
 * input is copied so that original input will not be changed.
 */
token
tokenizer::peek(std::string_view input) const
{
  token found_token = find_token(input);;
  return found_token; 
}

/*
 * discard a token and update input.
 */
void
tokenizer::consume(std::string_view& input)
{
  (void)get(input);
}

void
tokenizer::test_find_token(void)
{
  typedef token::type token_type;

  const std::vector<std::pair<std::string, std::vector<token>>> test_cases = {
    {"", {{"", token_type::invalid}}},
    {" ", {{"", token_type::invalid}}},
    {"a", {{"a", token_type::word}}},
    {"abc", {{"abc", token_type::word}}},
    {"1", {{"1", token_type::nonzero_digit}}},
    {"-1",
      {
        {"-", token_type::unary_op},
        {"1", token_type::nonzero_digit},
      }
    },
    {"1+23",
      {
        {"1", token_type::nonzero_digit},
        {"+", token_type::unary_op},
        {"23", token_type::nonzero_digit},
      }
    },
    {"-1+23",
      {
        {"-", token_type::unary_op},
        {"1", token_type::nonzero_digit},
        {"+", token_type::add_op},
        {"2", token_type::nonzero_digit},
      }
    },
    {" 12 + 3 ",
      {
        {"12", token_type::nonzero_digit},
        {"+", token_type::add_op},
        {"3", token_type::nonzero_digit},
      }
    },
    {"0", {{"0", token_type::zero}}},
    {".", {{"", token_type::invalid}}},
    {".1", {{"", token_type::invalid}}},
    {"0.", {{"0.", token_type::floating}}},
    {"0.123", {{"0.123", token_type::floating}}},
  };

  int count = 0;
  std::cout << "test_find_token\n";
  for (auto& tc: test_cases) {
    std::string_view str = tc.first;
    auto& answers = tc.second;
    token tkn;

    std::cout << count << ": " << str << '\n';
    for (auto& answer: answers) {
      tkn = find_token(str);
      if (tkn.data_ != answer.data_ || tkn.comp_type(answer.type_) == false) {
        std::cout << " X [" << tkn.data_ << ',' << static_cast<int>(tkn.type_) << "] != [";
        std::cout << answer.data_ << ',' << static_cast<int>(answer.type_) << "]\n";
        break;
      } else {
        std::cout << " O [" << tkn.data_ << ',' << static_cast<int>(tkn.type_) << "]\n";
      }
      
    }
    ++count;
  }
}

} // parsing
