#include "list.h"
#include <iostream>

int main() {
  List<int> list, list2;
  list2 = list.split(-5);
  list.print(std::cout);
  list2.print(std::cout);
  list.mergeWith(list2);
  list.print(std::cout);
  list2.print(std::cout);

  return 0;
}
