#include <iostream>
#include <type_traits>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/apply.hpp>

namespace higherordermf
{ 

  template<typename UnaryMetaFunctionClass, typename Arg>
  struct apply1
    : UnaryMetaFunctionClass::template apply<Arg>
  {};

  /*
  // metafunction twice
  template<typename T, typename F>
  struct twice
    : apply1<F, typename apply1<F, T>::type>
  {}; // ! metafunction twice
  */

  /*
  // metafunction twice
  template<typename T, typename F>
  struct twice
    : apply1< typename boost::mpl::lambda<F>::type // generates a metafunction class from a placeholder expression or if metafunction class, returns the same class.
            , typename apply1< typename boost::mpl::lambda<F>::type
                             , T
                             >::type>
  {}; // ! metafunction twice
  */

  // metafuncton twice
  template<typename T, typename F>
  struct twice
    : boost::mpl::apply< T
                       , typename boost::mpl::apply<F,T>::type
                       >
  {}; // ! metafunction twice

  // metafunction two_pointers
  template<typename T>
  struct two_pointers
    : twice< T
           , std::add_pointer<boost::mpl::placeholders::_1>
           >
  {}; // ! metafunction two_pointers

} // ! namespace higherordermf

int main()
{
  static_assert( std::is_same< higherordermf::two_pointers<int>::type
                             , int**
                             >::type::value
               , "both types should be int**"
               );

  return EXIT_SUCCESS;
}
