#include <iostream>
#include <cstdlib>
#include <boost/mpl/vector_c.hpp>
#include <type_traits>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <cassert>

namespace c3
{
  // Fundamental physical dimensions
  using mass = boost::mpl::vector_c<int,1,0,0,0,0,0,0>;
  using length = boost::mpl::vector_c<int,0,1,0,0,0,0,0>;
  using time = boost::mpl::vector_c<int,0,0,1,0,0,0,0>;
  using charge = boost::mpl::vector_c<int,0,0,0,1,0,0,0>;
  using temperature = boost::mpl::vector_c<int,0,0,0,0,1,0,0>;
  using intensity = boost::mpl::vector_c<int,0,0,0,0,0,1,0>;
  using angle = boost::mpl::vector_c<int,0,0,0,0,0,0,1>;

  // Compound physical dimensions
  using acceleration = boost::mpl::vector_c<int,0,1,-2,0,0,0,0>;
  using force = boost::mpl::vector_c<int,1,1,-2,0,0,0,0>;

  template<typename T, typename Dimension>
  class quantity
  {
  public:
    // 1-parameter constructor
    explicit quantity(T v)
      : m_value(v)
    {}

    template<typename OtherDimension>
    quantity(const quantity<T,OtherDimension>& q)
      : m_value(q.value())
    {
      static_assert(boost::mpl::equal<Dimension, OtherDimension>::type::value,
                    "Invalid conversion"
                    );
    }

    T value() const {return m_value;}

    // implicit conversion operator
    T operator()() const {return m_value;}

  private:
    T m_value;

  }; // struct quantity

  // Addition operator
  template<typename T, typename D>
  quantity<T,D>
  operator+(const quantity<T,D>& q1, const quantity<T,D>& q2)
  {
    return quantity<T,D>(q1.value() + q2.value());
  }

  // Subtraction operator
  template<typename T, typename D>
  quantity<T,D>
  operator-(const quantity<T,D>& q1, const quantity<T,D>& q2)
  {
    return quantity<T,D>(q1.value() - q2.value());
  }

  // Metafunction multiply_dimensions
  template<typename D1, typename D2>
  struct multiply_dimensions
    : boost::mpl::transform<D1,D2,boost::mpl::plus< boost::mpl::placeholders::_1, boost::mpl::placeholders::_2> >::type
  {}; // Metafunction divide_dimensions

  // Metafunction divide_dimensions
  template<typename D1, typename D2>
  struct divide_dimensions
    : boost::mpl::transform<D1,D2,boost::mpl::minus< boost::mpl::placeholders::_1, boost::mpl::placeholders::_2> >::type
  {}; // Metafunction divide_dimensions

  // Multiplication operator
  template<typename T, typename D1, typename D2>
  quantity<T, typename multiply_dimensions<D1,D2>::type>
  operator*(quantity<T,D1> q1, quantity<T,D2> q2)
  {
    return quantity<T, typename multiply_dimensions<D1,D2>::type>(q1.value()*q2.value());
  }

  // Division operator
  template<typename T, typename D1, typename D2>
  quantity<T, typename divide_dimensions<D1,D2>::type>
  operator/(quantity<T,D1> q1, quantity<T,D2> q2)
  {
    return quantity<T, typename divide_dimensions<D1,D2>::type>(q1.value()/q2.value());
  }

} // ! namespace c3

int main(int argc, char *argv[])
{
  c3::quantity<double, c3::mass> m1(4.0);
  c3::quantity<double, c3::mass> m2(8.0);
  auto m3 = m1 + m2;
  static_assert(std::is_same<decltype(m3), c3::quantity<double, c3::mass>>::value, "Types are not the same");

  c3::quantity<double, c3::acceleration> a(12.0);

  c3::quantity<double, c3::force> f = m1*a;
  assert(f.value() == 48.0);

  c3::quantity<double, c3::mass> m4 = f/a;
  assert(m4.value() == 4.0);

  return EXIT_SUCCESS;
}
