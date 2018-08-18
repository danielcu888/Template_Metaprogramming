#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <boost/mpl/if.hpp>
#include <vector>

namespace ex_4_5
{  
  template<typename Container, typename Value>
  typename boost::mpl::if_< std::is_const<Container>
                          , typename Container::const_iterator
                          , typename Container::iterator
                          >::type
  container_find(Container& c, const Value& v)
  {
    return std::find(c.begin(), c.end(), v);
  }
  
} // namespace ex_4_5

int main(int argc, char* argv[])
{
  const std::vector<int> cv {1,2,4,5,6,7,8};
  std::vector<int> v {3, 5};
  
  auto ci = ex_4_5::container_find<const std::vector<int>, int>(cv, 4);

  static_assert( std::is_same<decltype(ci), std::vector<int>::const_iterator>::value
               , "iterator should be const."
               );

  auto i = ex_4_5::container_find<std::vector<int>, int>(v, 3);

  static_assert( std::is_same<decltype(i), std::vector<int>::iterator>::value
               , "iterator should be non-const."
               );

  return 0;
}
