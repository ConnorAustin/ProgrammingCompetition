#include <iostream>

int main() {    
  int numbers;
  std::cin >> numbers;
  int total = 0;
  for(int n = 0; n < numbers; ++n) {
    int c;
    std::cin >> c;
    if(c < 0) {
      ++total;
    }
  }
  std::cout << total << std::endl;
}
