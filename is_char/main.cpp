#include <cstdlib>
#include <type_traits>

namespace example
{
/*
  template<typename T>
  struct NoCV
  {
    using type = T;
  };

  template<typename T>
  struct NoCV<const T>
  {
    using type = T;
  };

  template<typename T>
  struct NoCV<volatile T>
  {
    using type = T;
  };

  template<typename T>
  struct is_char
    : std::is_same<char, T>
  {};

  template<typename T>
  struct is_any_char
  : is_char<typename NoCV<T>::type>
  {};
*/

  template<typename T>
  struct is_any_char
    : std::is_same<typename std::remove_cv<T>::type, char>
  {};

} // ! namespace example

int main()
{
  static_assert(!example::is_any_char<int>::value, "whoops!");
  static_assert(example::is_any_char<volatile char>::value, "whoops!");

  return EXIT_SUCCESS;
}
