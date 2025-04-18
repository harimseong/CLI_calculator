#include <iostream>

#include "parsing/parser.hpp"
#include "parsing/ast.hpp"
#include "computing/analyzer.hpp"
#include "computing/computer.hpp"
#include "computing/data.hpp"
// #include "logger.hpp"
// #include "io/process_visualizer.hpp"

int main(int argc, char** argv)
{
  parsing::ast      t;
  parsing::parser   p;

  if (argc == 1) {
    // interactive
    std::cerr << argv[0] << ": interactive input is not supported.\n";
    return 1;
  }
  std::string_view  input(argv[1]);
  // parse argv[1] and if it is valid expression, solve it.
  if (p.parse(input, t) == false) {
    std::cerr << argv[0] << ": invalid input\n";
    return 1;
  }
  t.traverse();
  //analyzer::analyze(t);
  //computing::data solution = computing::compute(t);
  return 0;
}
