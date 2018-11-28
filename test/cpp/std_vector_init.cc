// Try to pass 0 to this cmd.
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char ** argv)
{
  if (argc < 2) {
    std::cout << "invalid parameters\n";
    return -1;
  }

  int num = 0;
  std::stringstream ss;
  ss << argv[1];
  ss >> num;
  std::vector<int> data(num);
  std::cout << "num=" << num << ", pointer=" << data.data() << std::endl;
  return 0;
}
