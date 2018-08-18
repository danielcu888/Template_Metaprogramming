#include <iostream>
#include <cstdlib>
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_member_function_pointer.hpp>
#include <boost/type_traits/is_member_pointer.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_const.hpp>

namespace ex_4_4
{

  template<typename T>
  struct is_data_member_pointer
    : boost::mpl::and_< boost::is_member_pointer<T>
                      , boost::mpl::not_< typename boost::is_member_function_pointer<T>::type >
                      >::type
  {}; // metafunction is_data_member_pointer

  template<typename T>
  struct is_pointer_to_function
    : boost::mpl::and_< boost::is_pointer<T>
                      , boost::is_function<typename boost::remove_pointer<T>::type>
                      >::type
  {};  // metafunction is_pointer_to_function
  
  template<typename T>
  struct is_reference_to_function_pointer
    : boost::mpl::and_< boost::is_reference<T>
                      , is_pointer_to_function<typename boost::remove_reference<T>::type>
                      >::type
  {}; // metafunction is_reference_to_function_pointer

  template<typename T>
  struct is_reference_to_non_const
    : boost::mpl::and_< boost::mpl::not_<typename boost::is_const<T>::type>
                      , boost::is_reference<T>
                        >::type
  {}; // is_reference_to_const

class foo;

} // namespace ex_4_4

int main(int argc, char *argv[])
{
  static_assert( ex_4_4::is_data_member_pointer<int ex_4_4::foo::*>::type::value
               , "int ex_4_4::foo* is a pointer to an int data member of ex4_4::foo"
               ); 

  static_assert( ex_4_4::is_pointer_to_function<int (*)(void)>::type::value
               , "int (*)(void) is a function pointer."
               );

  static_assert( ex_4_4::is_reference_to_function_pointer< int (*&)(void)>::type::value
               , "int (*&)(void) is a reference to a function pointer." 
               );

  static_assert( ex_4_4::is_reference_to_non_const<int&>::type::value
               , "int& is a reference to a non const type."
               );

  return EXIT_SUCCESS;
}
