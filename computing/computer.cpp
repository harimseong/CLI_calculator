#include "computer.hpp"

namespace computing
{

// constructors & destructor
computer::computer()
{
}

computer::~computer()
{
}

computer::computer(const computer& arg)
{
  (void)arg;
}

// operators
computer&
computer::operator=(const computer& arg)
{
  (void)arg;
  return *this;
}

}
