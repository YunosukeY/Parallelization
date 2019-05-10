#include <iostream>
// #include <cstring>
#include "clock.h"

int findSolution(int n);

int main(void)
{
  int n,count;
  std::cin >> n;
  start_counter();
  // ===== BEGIN =====
  count = findSolution(n);
  // ===== END =====
  print_counter();
  std::cout << count << std::endl;
  return 0;
}
