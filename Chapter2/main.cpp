#include <cstdlib>
#include <iostream>
#include <iterator>

/*
namespace std
{
  template<typename T>
  struct itertor_traits<T*>
  {
    using value_type = T;
    //...
  } // !iterator_traits
} // !namespace std
*/

namespace chapter2
{
  template<typename ForwardIterator1, typename ForwardIterator2>
  void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2)
  {
    typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
  }

  template<typename ForwardIterator>
  void iter_swap(ForwardIterator i1, ForwardIterator i2)
  {
    std::swap(*i1, *i2);
  }

} // !namespace chapter2

int main(int argc, char *argv[])
{
  // Example of iter_swap using builtin types
  int i1 {10};
  int i2 {20};

  std::cout << "Before:" << std::endl;
  std::cout << "i1: " << i1 << std::endl;
  std::cout << "i2: " << i2 << std::endl;
  
  chapter2::iter_swap<int*, int*>(&i1, &i2);

  std::cout << "After:" << std::endl;
  std::cout << "i1: " << i1 << std::endl;
  std::cout << "i2: " << i2 << std::endl;

  return EXIT_SUCCESS;
}
