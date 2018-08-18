#include <cstdlib>
#include <iostream>

namespace example
{

  /*
  template<std::size_t X, std::size_t N>
  struct pow
  {
    static const std::size_t value = pow<X,N-1>::value * X;
  };

  template<std::size_t X>
  struct pow<X,1>
  {
    static const std::size_t value = X;
  };

  template<std::size_t X>
  struct pow<X,0>
  {
    static const std::size_t value = 1;
  };
  */

  template<std::size_t N>
  struct pow
  {
    double operator()(double x) const {return x*pow<N-1>()(x);}
  };

  template<>
  struct pow<1>
  {
    double operator()(double x) const {return x;}
  };

  template<>
  struct pow<0>
  {
    double operator()(double x) const {return 1;}
  };

} // ! namespace example

int main()
{
  std::cout << example::pow<3>()(2.0) << std::endl;

  return EXIT_SUCCESS;
}
