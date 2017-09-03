#include <iostream>
#include <cmath>

int main() {
  double h;
  double v;
  std::cin >> h;
  std::cin >> v;
  
  std::cout << (int)std::ceil(h / sin(v * M_PI / 180.0)) << std::endl;
}
