#include "data.hpp"

namespace computing
{

// constructors & destructor
data::data()
{
}

data::~data()
{
}

data::data(const data& arg)
{
  (void)arg;
}

// operators
data&
data::operator=(const data& arg)
{
  (void)arg;
  return *this;
}

}
