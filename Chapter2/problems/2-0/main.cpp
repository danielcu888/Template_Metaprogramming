#include <cstdlib>
#include <iostream>
#include <type_traits>

template<typename T, bool = std::is_reference<T>::value>
struct add_const_ref
{
  using type = 
    typename std::add_lvalue_reference<
      typename std::add_const<
        typename std::remove_reference<T>::type
      >::type
    >::type;
};

template<typename T>
struct add_const_ref<T, false>
{
  using type = 
    typename std::add_lvalue_reference<typename std::add_const<T>::type>::type;
};

int main(int argc, char *argv[])
{
  // Test 1: int
  static_assert(std::is_same<const int&, add_const_ref<int>::type>::value,
                "Test for int has failed.");
  // Test 2: int&
  static_assert(std::is_same<const int&, add_const_ref<int&>::type>::value,
                "Test for int& has failed.");

  // Test 3: const int&
  static_assert(std::is_same<const int&, add_const_ref<const int&>::type>::value,
                "Test for const int& has failed.");

  return EXIT_SUCCESS;
}
