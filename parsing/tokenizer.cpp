#include <vector>
#include <string>
#include <iostream>

#include "tokenizer.hpp"
#include "parsing/token.hpp"

namespace parsing
{

/*
 * @return update input and current token.
 */
void
tokenizer::consume(std::string_view& input)
{
  token new_token;
  size_t token_size;

  do {
    new_token = find_token(input);
    token_size = new_token.data_.size();
    input = input.substr(token_size, input.size() - token_size);
  } while (new_token.comp_type(token::whitespace) == true);
  cur_token_ = new_token;
}

/*
 * @return current token after update
 */
token
tokenizer::get(std::string_view& input)
{
  token cur_token;

  if (cur_token_.type_pack_ == token::init) {
    consume(input);
  }
  cur_token = cur_token_;
  consume(input);
  return cur_token;
}

/*
 * @return current token without update
 */
token
tokenizer::peek(std::string_view& input)
{
  if (cur_token_.type_pack_ == token::init) {
    consume(input);
  }
  return cur_token_; 
}

void
tokenizer::test_find_token(void)
{
  typedef token::type token_type;

  const std::vector<std::pair<std::string, std::vector<token>>> test_cases = {
    {"", {{"", token_type::eol}}},
    {" ", {{"", token_type::eol}}},
    {"a", {{"a", token_type::word}}},
    {" a ", {{"a", token_type::word}}},
    {"abc", {{"abc", token_type::word}}},
    {"1", {{"1", token_type::integer}}},
    {" 1 ", {{"1", token_type::integer}}},
    {"-1",
      {
        {"-", token_type::unary_op},
        {"1", token_type::integer},
      }
    },
    {"1+23",
      {
        {"1", token_type::integer},
        {"+", token_type::unary_op},
        {"23", token_type::integer},
      }
    },
    {"-1+23",
      {
        {"-", token_type::unary_op},
        {"1", token_type::integer},
        {"+", token_type::add_op},
        {"23", token_type::integer},
      }
    },
    {" 12 + 3 ",
      {
        {"12", token_type::integer},
        {"+", token_type::add_op},
        {"3", token_type::integer},
      }
    },
    {"0", {{"0", token_type::zero}}},
    {".", {{"", token_type::invalid}}},
    {".1", {{"", token_type::invalid}}},
    {"0.", {{"0.", token_type::floating}}},
    {"0.123", {{"0.123", token_type::floating}}},
    {"(1)",
      {
        {"(", token_type::parenthesis},
        {"1", token_type::integer},
        {")", token_type::parenthesis},
      }
    },
  };

  int count = 0;
  std::cout << "test_find_token\n";
  for (auto& tc: test_cases) {
    std::string_view str = tc.first;
    auto& answers = tc.second;
    token tkn;
    tokenizer scanner;

    std::ios_base::fmtflags ff = std::cout.flags(std::ios_base::hex);
    std::cout << count << ": \"" << str << "\"\n";
    for (auto& answer: answers) {
      tkn = scanner.get(str);
      if (tkn.data_ != answer.data_ || tkn.comp_type(answer.type_pack_) == false) {
        std::cout << " X [" << tkn.data_ << ',' << static_cast<int>(tkn.type_pack_) << "] != [";
        std::cout << answer.data_ << ',' << static_cast<int>(answer.type_pack_) << "]\n";
        break;
      } else {
        std::cout << " O [" << tkn.data_ << ',' << static_cast<int>(tkn.type_pack_) << "]\n";
      }
    }
    std::cout.flags(ff);
    ++count;
  }
}

} // parsing
