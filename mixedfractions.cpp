#include <iostream>

int main() {
  while (true) {
    long num;
    std::cin >> num;
    
    long den;
    std::cin >> den;

    if (den == 0) {
      return 0;
    }
    
    long whole = num / den;
    num %= den;
    
    std::cout << whole << " " << num << " / " << den << std::endl;
  }
}
