#include <iostream>
#include <array>
#include <algorithm>

int main() {
  std::array<int, 4> x;
  std::cin >> x[0];
  std::cin >> x[1];
  std::cin >> x[2];
  std::cin >> x[3];
  
  std::sort(std::begin(x), std::end(x));
  std::cout << (x[0] * x[2]) << std::endl;
}
