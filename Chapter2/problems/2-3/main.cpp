#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>

// Primary Template
template< typename T
        , typename C = typename std::is_const<T>::type
        , typename V = typename std::is_volatile<T>::type
        , typename P = typename std::is_pointer<T>::type
        , typename L = typename std::is_lvalue_reference<T>::type
        , typename R = typename std::is_rvalue_reference<T>::type
        >
struct type_descriptor
{
  std::string operator()() const
  {
    return "Default implementation!!!";
  }
};

// ! Primary Template

// Explicit Specializations

// int
template<>
struct type_descriptor<int>
{
  std::string operator()() const
  {
    return "int";
  }
};

// char
template<>
struct type_descriptor<char>
{
  std::string operator()() const
  {
    return "char";
  }
};

// long
template<>
struct type_descriptor<long>
{
  std::string operator()() const noexcept
  {
    return "long";
  }
};

// short int
template<>
struct type_descriptor<short int>
{
  std::string operator()() const noexcept
  {
    return "short int";
  }
};

// ! Explicit Specializations

// Partial Specializations

// const types
template<typename T>
struct type_descriptor< T
                      , std::true_type
                      >
{
  std::string operator()() const noexcept
  {
    type_descriptor<std::remove_const_t<T>> p;
    return p() + " const";
  }
};

// volatile types
template<typename T>
struct type_descriptor< T
                      , std::false_type
                      , std::true_type
                      >
{
  std::string operator()() const noexcept
  {
    type_descriptor<std::remove_volatile_t<T>> p;
    return p() + " volatile";
  }
};

// pointer types
template<typename T>
struct type_descriptor< T
                      , std::false_type
                      , std::false_type
                      , std::true_type
                      >
{
  std::string operator()() const noexcept
  {
    type_descriptor<std::remove_pointer_t<T>> p;
    return p() + "*";
  }
};

// l-value references
template<typename T>
struct type_descriptor< T
                      , std::false_type
                      , std::false_type
                      , std::false_type
                      , std::true_type
                      >
{
  std::string operator()() const noexcept
  {
    type_descriptor<std::remove_reference_t<T>> p;
    return p() + "&";
  }
};

// r-value references
template<typename T>
struct type_descriptor< T
                      , std::false_type
                      , std::false_type
                      , std::false_type
                      , std::false_type
                      , std::true_type
                      >
{
  std::string operator()() const noexcept
  {
    type_descriptor<std::remove_reference_t<T>> p;
    return p() + "&&";
  }
};

// ! Partial Specializations

// Insertion operator
template< typename T
        , typename C
        , typename V
        , typename P
        , typename L
        , typename R
        >
std::ostream& operator<<( std::ostream& os
                        , const type_descriptor<T,C,V,P,L,R>& td
                        )
{
  os << td();
  return os;
}

// ! Insertion operator

// main
int main(int argc, char *argv[])
{
  // Examples
  std::cout << type_descriptor<int>() << std::endl;
  std::cout << type_descriptor<char*>() << std::endl;
  std::cout << type_descriptor<volatile long const*&>() << std::endl;

  return EXIT_SUCCESS;
}
// ! main
