#include <iostream>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/end.hpp>

namespace ex
{
  // Check if type is in a collection of types
  using types = boost::mpl::vector<char,int,unsigned,long,unsigned long, bool>;
  const bool result = boost::mpl::contains<types,bool>::type::value;
  static_assert(result, "bool should be in the vector");

  using iter = boost::mpl::find<types, float>::type;
  static_assert(iter::pos::value == boost::mpl::end<types>::type::value, "");

  // Check how many times type is in the collection of types
  using count_types = boost::mpl::vector<char,int,unsigned,long,bool,unsigned long, bool>;
  const unsigned int count_result = boost::mpl::count<count_types,bool>::type::value;
  static_assert(count_result == 2, "bool should be in the vector twice");

  // Count how many times each elemetn of a sequence of types is contained in a given collection of types.
  using seq1 = boost::mpl::vector<double, char, int>;
  using seq2 = boost::mpl::vector<int, char, long, char>;
  using result2 = boost::mpl::transform< seq1, boost::mpl::count<seq2, boost::mpl::placeholders::_1> >::type;

  static_assert(boost::mpl::at_c<result2,0>::type::value == 0, "Should find 1 double");
  static_assert(boost::mpl::at_c<result2,1>::type::value == 2, "Should find 2 char's");
  static_assert(boost::mpl::at_c<result2,2>::type::value == 1, "Should find 1 int");

} // ! namepsace ex

int main()
{
  return EXIT_SUCCESS;
}
