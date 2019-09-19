#ifndef FRUIT_H_
#define FRUIT_H_

#include <string>

class Fruit {
 public:
  Fruit(size_t type_index, size_t value);
  ~Fruit();
  const std::string& type() const { return type_; }
  size_t value() const { return value_; }

 private:
  static char const* fruit_types[];

  std::string type_;
  size_t value_;
};

#endif
