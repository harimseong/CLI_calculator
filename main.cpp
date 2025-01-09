#include "parsing/parser.hpp"
#include "parsing/ast.hpp"
#include "computing/analyzer.hpp"
#include "computing/computer.hpp"
#include "computing/data.hpp"
// #include "logger.hpp"
// #include "io/process_visualizer.hpp"

int main(int argc, char** argv)
{
  if (argc == 1) {
    // interactive
  }
  (void)argv;
  // parse argv[1] and if it is valid expression, solve it.
  parsing::ast t;

  //parsing::parse(argv[1], t);
  //computing::analyze(t);
  //computing::data solution = computing::compute(t);
  return 0;
}
