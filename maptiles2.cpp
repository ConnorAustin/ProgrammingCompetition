#include <iostream>
#include <cmath>

int main() {
  std::string quadkey;
  std::cin >> quadkey;
  
  int x = 0;
  int y = 0;
  for(int c = 0; c < quadkey.length(); ++c) {
    int s = std::pow(2, quadkey.length() - 1 - c);
    x += quadkey[c] == '3' || quadkey[c] == '1' ? s : 0;
    y += quadkey[c] == '3' || quadkey[c] == '2' ? s : 0;
  }
  std::cout << quadkey.length() << " " << x << " " << y << std::endl;
}
