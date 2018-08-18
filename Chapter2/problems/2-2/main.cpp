#include <cstdlib>
#include <iostream>
#include <cassert>
#include <type_traits>

class A
{
 public:
  virtual ~A() = default;
};

class B : public A
{
 public:
  virtual ~B() = default;
};

// Initial implementation
template<typename Target, typename Source>
Target* polymorphic_downcast(Source *s)
{
  assert(dynamic_cast<Target*>(s) == s);
  return static_cast<Target*>(s);
}

// New implementation
template<typename Target, typename Source>
Target polymorphic_downcast2(Source s)
{
  static_assert((std::is_lvalue_reference<Source>::value && std::is_lvalue_reference<Target>::value &&
                 std::is_base_of<typename std::remove_reference<Source>::type, typename std::remove_reference<Target>::type>::value) ||
                (std::is_pointer<Source>::value && std::is_pointer<Target>::value &&
                 std::is_base_of<typename std::remove_pointer<Source>::type, typename std::remove_pointer<Target>::type>::value),
                "Invalid types");
  return static_cast<Target>(s);
}


int main(int argc, char *argv[])
{
  B b;
  A* ap = &b;
  // Initial implementation
  B* bp = polymorphic_downcast<B,A>(ap);

  // New implementation
  B* bp2 = polymorphic_downcast2<B*,A*>(ap);
  return EXIT_SUCCESS;
}
