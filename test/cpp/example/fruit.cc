#include "fruit.h"

#include <cassert>
#include <iostream>

char const* Fruit::fruit_types[] = {"apple", "banana", "cherry", "lemon"};

Fruit::Fruit(size_t type_index, size_t value) {
  assert(0 <= type_index && sizeof(fruit_types) > type_index);
  type_ = std::string(fruit_types[type_index]);
  value_ = value;
  std::cout << "New " << type_ << " " << value_ << std::endl;
}

Fruit::~Fruit() {
  std::cout << "Delete " << type_ << std::endl;
}
