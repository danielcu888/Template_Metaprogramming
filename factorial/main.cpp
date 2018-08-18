#include <cstdlib>
#include <iostream>
#include <type_traits>

namespace factorial
{
  /*
  // The purpose of this class is to represent an compile-time integral constant as a type.
  template < typename T // The type
           , T v        // The value of the type associated with this struct
           >
  struct integral_constant
  {
    static constexpr T value = v;

    using type = integral_constant<T,v>;
    using value_type = T;

    constexpr operator T() { return v; }
  };
  */

template<std::size_t n>
struct factorial
  : std::integral_constant<std::size_t, n*factorial<n-1>::value>
{};

// since factorial is a class we can partially specialize for n = 0
template<>
struct factorial<0>
  : std::integral_constant<std::size_t, 1>
{};

} // ! namespace factorial

int main(int argc, char* argv[])
{
  std::cout << factorial::factorial<5>::value << std::endl;
  
  return EXIT_SUCCESS;
}
