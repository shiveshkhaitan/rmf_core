#ifndef ABSTRACT_HPP
#define ABSTRACT_HPP

class Abstract
{
public:
  virtual double get_value() = 0;
};

class TaskFactory
{
public:
  virtual std::shared_ptr<Abstract> get_abstract(double value) = 0;
};

#endif // ABSTRACT_HPP
