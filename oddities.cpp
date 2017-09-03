#include <iostream>

int main() {
  int count;
  std::cin >> count;
  
  for(int i = 0; i < count; ++i) {
    int num;
    std::cin >> num;
    
    if(num % 2 == 0) {
      std::cout << num << " is even" << std::endl;
    } else {
      std::cout << num << " is odd" << std::endl;
    }
  }
}
