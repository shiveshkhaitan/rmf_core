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

class DerivedTaskFactory : public TaskFactory
{
public:
  DerivedTaskFactory()
  {}

  ~DerivedTaskFactory()
  {}

  std::shared_ptr<Abstract> get_abstract(double value) final
  {
    std::shared_ptr<Derived> derived(new Derived(value));
    return derived;
  }
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

  std::shared_ptr<DerivedTaskFactory> derived_task_factory(
      new DerivedTaskFactory());
  auto new_derived = derived_task_factory->get_abstract(420);
  call_get_value(new_derived);

  std::cout << "all done" << std::endl;
  return 0;
}
