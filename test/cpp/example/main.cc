#include <cstddef>
#include <iostream>
#include <sstream>

#include "fruit.h"
#include "thread.h"

#define NUM 4

int main(int argc, char ** argv) {
  if (argc < 3) {
    std::cout << "Require at least 2 parameters" << std::endl;
    return -1;
  }

  Thread* threads[NUM];
  for (int i = 0; i < NUM; i += 1) {
    threads[i] = new Thread(std::to_string(i + 1));
  }

  for (int i = 1; i < argc; i += 2) {
    size_t type_index = 0;
    switch (argv[i][0]) {
      case 'a':
	type_index = 0;
	break;
      case 'b':
	type_index = 1;
	break;
      case 'c':
	type_index = 2;
	break;
      case 'l':
	type_index = 3;
	break;
      default:
	break;
    }
    std::istringstream in_stream(argv[i + 1]);
    size_t value = 0;
    in_stream >> value;
    Fruit* f = new Fruit(type_index, value);
    threads[type_index]->Consume(f);
  }

  for (int i = 0; i < NUM; i += 1) {
    delete threads[i];
    threads[i] = nullptr;
  }

  return 0;
}
