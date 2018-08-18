#include <cstdlib>

namespace example
{

  template<size_t N>
  struct sum
  {
    static const std::size_t value = sum<N-1>::value + N;
  };

  template<>
  struct sum<1>
  {
    static const std::size_t value = 1;
  };

} // ! namespace example

int main()
{
  static_assert(example::sum<3>::value == 6, "shit");

  return EXIT_SUCCESS;
}
