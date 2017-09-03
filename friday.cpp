#include <iostream>

int main() {
  int cases;
  std::cin >> cases;
  
  for(int c = 0; c < cases; ++c) {
    int months;
    std::cin >> months;
    std::cin >> months;
    
    int curDay = 0;
    int result = 0;
    
    for(int m = 0; m < months; ++m) {
      int daysInMonth;
      std::cin >> daysInMonth;
      
      if(daysInMonth >= 13 && (curDay + 13) % 7 == 6) {
        ++result;
      }
      curDay += daysInMonth;
    }
    std::cout << result << std::endl;
  }
}
