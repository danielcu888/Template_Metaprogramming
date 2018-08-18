#include <cstdlib>
#include <iostream>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <type_traits>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/placeholders.hpp>

namespace dimensions
{

  /*
  using dimension = int[7];
  const dimension mass = {1,0,0,0,0,0,0};
  const dimension length = {0,1,0,0,0,0,0};
  const dimension time = {0,0,1,0,0,0,0};

  const dimension force = {1,1,-2,0,0,0,0};
  */

  /*
  using mass = boost::mpl::vector< boost::mpl::int_<1>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 >;
  using length = boost::mpl::vector< boost::mpl::int_<0>
                                   , boost::mpl::int_<1>
                                   , boost::mpl::int_<0>
                                   , boost::mpl::int_<0>
                                   , boost::mpl::int_<0>
                                   , boost::mpl::int_<0>
                                   , boost::mpl::int_<0>
                                   >;
  using time = boost::mpl::vector< boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<1>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 , boost::mpl::int_<0>
                                 >;

  using force = boost::mpl::vector< boost::mpl::int_<1>
                                  , boost::mpl::int_<1>
                                  , boost::mpl::int_<-2>
                                  , boost::mpl::int_<0>
                                  , boost::mpl::int_<0>
                                  , boost::mpl::int_<0>
                                  , boost::mpl::int_<0>
                                  >;
  */

  using mass = boost::mpl::vector_c<int,1,0,0,0,0,0,0>;
  using length = boost::mpl::vector_c<int,0,1,0,0,0,0,0>;
  using time = boost::mpl::vector_c<int,0,0,1,0,0,0,0>;
  using charge = boost::mpl::vector_c<int,0,0,0,1,0,0,0>;
  using temperature = boost::mpl::vector_c<int,0,0,0,0,1,0,0>;
  using intensity = boost::mpl::vector_c<int,0,0,0,0,0,1,0>;
  using angle = boost::mpl::vector_c<int,0,0,0,0,0,0,1>;

  using velocity = boost::mpl::vector_c<int,0,1,-1,0,0,0,0>;
  using acceleration = boost::mpl::vector_c<int,0,1,-2,0,0,0,0>;
  using momentum = boost::mpl::vector_c<int,1,1,-1,0,0,0,0>;
  using force = boost::mpl::vector_c<int,1,1,-2,0,0,0,0>;
  using scalar = boost::mpl::vector_c<int,0,0,0,0,0,0,0>;

  
  // Class quantity
  template<typename T, typename Dimension>
  class quantity
  {
  public:
    explicit quantity(const T& value)
      : m_value(value)
    {}

    template<typename OtherDimension>
    quantity(const quantity<T, OtherDimension>& other)
      : m_value(other.value())
    {
      static_assert( boost::mpl::equal<OtherDimension, Dimension>::type::value
                   , "Dimensions are incompatible."
                   );
    }

    T value() const {return m_value;}

  private:
    T m_value;

  }; // ! class quantity

  // Addition operator
  template<typename T, typename D>
  const quantity<T, D>
  operator+(const quantity<T,D>& lhs, const quantity<T, D>& rhs)
  {
    return quantity<T,D>(lhs.value()+rhs.value());
  }

  // Subtraction operator
  template<typename T, typename D>
  const quantity<T, D>
  operator-(const quantity<T,D>& lhs, const quantity<T, D>& rhs)
  {
    return quantity<T,D>(lhs.value()-rhs.value());
  }

  struct plus_f
  {
    template<typename T1, typename T2>
    struct apply
      : boost::mpl::plus<T1,T2>
    {};

  }; // metafunction class plus_f

  /*
  struct minus_f
  {
    template<typename T1, typename T2>
    struct apply
      : boost::mpl::minus<T1,T2>
    {};

  }; // metafunction class minus_f

  // Multiplication operator
  template<typename T, typename D1, typename D2>
  const quantity<T, typename boost::mpl::transform<D1, D2, plus_f>::type>
  operator*(const quantity<T,D1>& lhs, const quantity<T,D2>& rhs)
  {
    using dim = typename boost::mpl::transform<D1, D2, plus_f>::type;
    return quantity<T, dim>(lhs.value()*rhs.value());

  } // quantity operator*

  // Division operator
  template<typename T, typename D1, typename D2>
  const quantity<T, typename boost::mpl::transform<D1,D2,minus_f>::type>
  operator/(const quantity<T,D1>& lhs, const quantity<T,D2>& rhs)
  {
    using dim = typename boost::mpl::transform<D1,D2,minus_f>::type;
    return quantity<T,dim>(lhs.value()/rhs.value());

  } // quantity operator/
  */

  template<typename D1, typename D2>
  struct product_dimensions
    : boost::mpl::transform<D1, D2, boost::mpl::plus<boost::mpl::placeholders::_1, boost::mpl::placeholders::_2> >
  {};

  // Multiplication operator
  template<typename T, typename D1, typename D2>
  const quantity<T, typename product_dimensions<D1,D2>::type>
  operator*(const quantity<T,D1>& lhs, const quantity<T,D2>& rhs)
  {
    return quantity<T, typename product_dimensions<D1,D2>::type>(lhs.value()*rhs.value());

  } // quantity operator*

  template<typename D1, typename D2>
  struct divide_dimensions
    : boost::mpl::transform<D1, D2, boost::mpl::minus<boost::mpl::placeholders::_1, boost::mpl::placeholders::_2> >
  {};

  // Division operator
  template<typename T, typename D1, typename D2>
  const quantity<T, typename divide_dimensions<D1,D2>::type>
  operator/(const quantity<T,D1>& lhs, const quantity<T,D2>& rhs)
  {
    return quantity<T,typename divide_dimensions<D1,D2>::type>(lhs.value()/rhs.value());=

  } // quantity operator/

} // ! namespace dimensions


int main(int argc, char *argv[])
{
  dimensions::quantity<double, dimensions::length> l(1.0);
  dimensions::quantity<double, dimensions::mass> m(2.0);
  dimensions::quantity<double, dimensions::mass> m2 = m + m;
  dimensions::quantity<double, dimensions::acceleration> a(9.81);

  dimensions::quantity<double, dimensions::force> f = m*a;
  std::cout << f.value() << std::endl;

  dimensions::quantity<double, dimensions::mass> m3 = f / a;
  std::cout << m3.value() << std::endl;

  return EXIT_SUCCESS;
}
