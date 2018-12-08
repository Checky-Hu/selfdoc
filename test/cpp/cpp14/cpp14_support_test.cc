#include <iostream>
#include <optional>
#include <string>

auto create_optional(bool flag)
{
  return flag ?
      std::optional<std::string>{"Hello world!"} :
      std::nullopt;
}

int main(int argc, char ** argv)
{
  bool flag = argc > 1 ? true : false;

  auto var = create_optional(flag);
  if (var)
    std::cout << "var=" << *var << std::endl;
  else
    std::cout << "no param no var" << std::endl;

  return 0;
}
