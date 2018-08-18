#include <iostream>
#include <cstdlib>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/int.hpp>
#include <type_traits>
#include <boost/mpl/equal_to.hpp>

namespace ex_4_1
{
  template<typename T, typename Q>
  struct logical_or_
    : boost::mpl::eval_if_c<
       T::type::value || Q::type::value
       , boost::mpl::bool_<true>
       , boost::mpl::bool_<false>
    >::type // added type here so that behaviour is the same as mpl::or_ and we can call value directly
  {}; // metafunction logical_or

  template<typename T>
  struct is_one_or_two
    : logical_or_< boost::mpl::equal_to<T, boost::mpl::int_<1>>
                 , boost::mpl::equal_to<T, boost::mpl::int_<2>>
                 >
    {}; // metafunction one_or_two

  template<typename T, typename Q>
  struct logical_and_
    : boost::mpl::eval_if_c<
       T::type::value && Q::type::value
       , boost::mpl::bool_<true>
       , boost::mpl::bool_<false>
    >::type // added type here so that behaviour is the same as mpl::and_ and we can call value directly
  {}; // metafunction logical_and

  template<typename T>
  struct is_one_and_two
    : logical_and_< boost::mpl::equal_to<T, boost::mpl::int_<1>>
                  , boost::mpl::equal_to<T, boost::mpl::int_<2>>
                  >
    {}; // metafunction one_or_two

} // namespace 4_1

int main(int argc, char *argv[])
{
  // Test for boost::mpl::or_ (uses short-circuit because satisfies first condition).
  static_assert(ex_4_1::is_one_or_two<boost::mpl::int_<1>>::value, "Should be 1");

  // Test for boost::mpl::and_ (uses short-circuit because fails first condition).
  static_assert(!ex_4_1::is_one_and_two<boost::mpl::int_<3>>::value, "Should not be 1 or 2");

  return EXIT_SUCCESS;
}
