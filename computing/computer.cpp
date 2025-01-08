#include "computer.hpp"

// constructors & destructor
computer::computer()
{
}

computer::~computer()
{
}

computer::computer(const computer& computer)
{
  (void)computer;
}

// operators
computer&
computer::operator=(const computer& computer)
{
  (void)computer;
  return *this;
}
