#include "analyzer.hpp"

namespace computing
{

// constructors & destructor
analyzer::analyzer()
{
}

analyzer::~analyzer()
{
}

analyzer::analyzer(const analyzer& arg)
{
  (void)arg;
}

// operators
analyzer&
analyzer::operator=(const analyzer& arg)
{
  (void)arg;
  return *this;
}

}
