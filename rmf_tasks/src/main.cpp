#include <memory>
#include <iostream>

#include "abstract.hpp"

class Derived : public Abstract
{
public:

  Derived(double value)
  : _val(value)
  {}

  ~Derived()
  {}

  double get_value() final
  {
    return _val;
  }

private:
  double _val;

};

void call_get_value(std::shared_ptr<Abstract> base)
{
  if (!base)
    std::cout << "whoops it was a nullptr" << std::endl;

  std::cout << "called " << base->get_value() << std::endl;
}

int main(int argc, char** argv)
{
  std::shared_ptr<Derived> derived(new Derived(42));
  call_get_value(derived);

  std::cout << "all done" << std::endl;
  return 0;
}
