#include <cstdlib>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/int.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <type_traits>
#include <boost/mpl/placeholders.hpp>

namespace ex_4_3
{
  template<typename N, typename Predicate>
  struct next_if
    : boost::mpl::if_< typename boost::mpl::apply<Predicate, N>::type
                     , typename boost::mpl::next<N>::type
                     , N
                     >
  {}; // metafunction next_if

  template<typename N, typename Predicate>
  struct next_if_improved
    : boost::mpl::eval_if< typename boost::mpl::apply<Predicate, N>::type
                          , boost::mpl::next<N>
                          , boost::mpl::identity<N>
                          >
  {}; // metafunction next_if_improved

  template<typename N1, typename N2>
  struct formula
    : boost::mpl::if_< boost::mpl::not_equal_to<N1,N2>
                       , typename boost::mpl::if_< boost::mpl::greater<N1,N2>
                                                   , typename boost::mpl::minus<N1,N2>::type
                                                   , N1
                                                   >::type
                       , typename boost::mpl::plus< N1
                                                    , typename boost::mpl::multiplies< N1
                                                                                     , boost::mpl::int_<2>::type
                                                                                     >::type
                                                    >::type
                       >::type
  {}; // metafunction formula

  template<typename N1, typename N2>
  struct formula_improved
    : boost::mpl::eval_if< boost::mpl::not_equal_to<N1,N2>
                          , boost::mpl::eval_if< boost::mpl::greater<N1,N2>
                                                , boost::mpl::minus<N1,N2>
                                                , boost::mpl::identity<N1>
                                                >
                          , boost::mpl::plus< N1
                                            , typename boost::mpl::multiplies< N1
                                                                            , boost::mpl::int_<2>::type
                                                                            >::type
                                            >
                          >
  {}; // metafunction formula_improved

} // namespace 4_3

int main(int argc, char *argv[])
{
  static_assert( ex_4_3::next_if< boost::mpl::int_<2>
                                , boost::mpl::equal_to< boost::mpl::placeholders::_1, boost::mpl::int_<2> > 
                                >::type::value == 3
               , "3 does not follow 2?!?"
               );

  static_assert( ex_4_3::next_if_improved< boost::mpl::int_<2>
                                         , boost::mpl::equal_to< boost::mpl::placeholders::_1, boost::mpl::int_<2> > 
                                         >::type::value == 3
               , "3 does not follow 2?!?"
               );

  static_assert( ex_4_3::formula< boost::mpl::int_<1>
                                , boost::mpl::int_<1>
                                >::type::value == 3
               , "1+1*2 != 3!?!"
               );

  static_assert( ex_4_3::formula_improved< boost::mpl::int_<1>
                                         , boost::mpl::int_<1>
                                         >::type::value == 3
               , "1+1*2 != 3!?!"
               );
 
  return EXIT_SUCCESS;
}
