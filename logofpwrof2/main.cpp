#include <cstdlib>
#include <type_traits>
#include <iostream>

namespace example
{

  template<std::size_t N>
  struct log2
  {
    static const std::size_t value = 1 + log2<N/2>::value;
  };

  template<>
  struct log2<1>
  {
    static const std::size_t value = 0;
  };

} // ! namespace example

int main()
{
  static_assert(example::log2<1>::value == 0, "shit");

  return EXIT_SUCCESS;
}
