#include <iostream>
#include <cmath>

int main() {
  int cases;
  std::cin >> cases;
  
  std::string junk;
  std::getline(std::cin, junk);

  for (int c = 0; c < cases; ++c) {
    std::string line;
    std::getline(std::cin, line);
    
    std::string out;
    
    int k = (int) std::ceil(std::sqrt((double)line.length()));

    for (int x = 0; x < k; ++x) {
      for (int y = k - 1; y > -1; --y) {
        int index = x + y * k;
        if (index < line.length()) {
          out += line[index];
        }
      }
    }
    std::cout << out << std::endl;
  }
}
