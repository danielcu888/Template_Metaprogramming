#include <type_traits>
#include <iostream>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

namespace ex_4_1_1
{
  template<typename T>
  struct param_type
    : boost::mpl::eval_if_c< std::is_scalar<T>::type::value
                           , boost::mpl::identity<T>
                           , std::add_lvalue_reference<const T>
                           >
  {};

/*
  {
  #include <boost/mpl/placeholders.hpp>

  using boost::mpl::placeholders::_1;
  boost::mpl::transform< input_sequence // e.g., boost::mpl::vector_c<int,double>
                       , boost::mpl::eval_if_c< boost::mpl::bool_<std::is_scalar<_1>::type::value || std::is_reference<_1>::type::value>::type::value
                                              , boost::mpl::identity<_1>
                                              , std::add_lvalue_reference<const _1>
                                              >
                         >::type; // should return sequence {int, double} since the input sequence types are scalar.}
}
*/
  // ADT
  struct Foo {};

  /*
  template< typename T1, typename T2>
  struct check_types_are_equal
  {
    static_assert(std::is_same<T1, T2>::value, "Types do not match!");

  }; // not a metafunction, just a convenience function wrapping std::is_same.
     // this seems wrong. All we want is to preserve the fail message. PErhaps a macro?
     // macro takes the two input arguments and failure msg and conducts the static assert.
  */

  //const char* failure_msg = "Types are not equal.";

} // namespace ex_4_1_1

int main(int argc, char *argv[])
{
  static_assert(std::is_same<typename ex_4_1_1::param_type<int>::type, int>::type::value, "Types are not equal.");
  static_assert(std::is_same<typename ex_4_1_1::param_type<ex_4_1_1::Foo>::type, const ex_4_1_1::Foo&>::type::value, "Types are not equal.");
}
