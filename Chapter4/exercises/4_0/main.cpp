#include <iostream>
#include <cstdlib>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/int.hpp>
#include <type_traits>
#include <boost/mpl/and.hpp>

namespace ex_4_0
{
  template<typename T>
  struct is_one_or_two
    : boost::mpl::or_< boost::mpl::equal_to<T, boost::mpl::int_<1>>
                     , boost::mpl::equal_to<T, boost::mpl::int_<2>>
                     >
    {}; // metafunction one_or_two

  template<typename T>
  struct is_one_and_two
    : boost::mpl::and_< boost::mpl::equal_to<T, boost::mpl::int_<1>>
                      , boost::mpl::equal_to<T, boost::mpl::int_<2>>
                      >
    {}; // metafunction one_or_two

} // namespace ex_4_0

int main(int argc, char *argv[])
{
  // Test for boost::mpl::or_ (uses short-circuit because satisfies first condition).
  static_assert(ex_4_0::is_one_or_two<boost::mpl::int_<1>>::value, "Should be 1");

  // Test for boost::mpl::and_ (uses short-circuit because fails first condition).
  static_assert(!ex_4_0::is_one_and_two<boost::mpl::int_<3>>::value, "Should not be 1 or 2");

  return EXIT_SUCCESS;
}
