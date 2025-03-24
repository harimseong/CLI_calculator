#ifndef DATA_HPP
#define DATA_HPP

#include <cstdint>

namespace computing
{

class  data
{
public:
// constructors & destructor
  data();
  ~data();
  data(const data&);

// operators
  data	&operator=(const data&);

private:
  union {
    int64_t integer_;
    double  fp_;
  };
};

}

#endif // DATA_HPP
