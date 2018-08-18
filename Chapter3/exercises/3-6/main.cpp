#include <cstdlib>
#include <boost/mpl/apply.hpp>
#include <type_traits>
#include <boost/mpl/placeholders.hpp>

namespace ex
{

// Metafunction implemented using a lambda
// expression that twice applies the
// lambda expression F (i.e., metafunction class or
// placeholder expression) to metadata X. 
template<typename F, typename X>
struct twice
{
  using type
    = typename boost::mpl::apply< F
                                , typename boost::mpl::apply< F
                                                            , X
                                                            >::type
                                >::type;

}; // ! metafunction twice

} // ! namespace ex

int main(int argc, char *argv[])
{

  static_assert( std::is_same< typename ex::twice< std::add_pointer<boost::mpl::placeholders::_1>
                                                 , int
                                                 >::type
                             , int**
                             >::type::value
               , "Types should both be int**."
               );

  return EXIT_SUCCESS;
}
