#include <iostream>

int digitSum(int n) {
  int sum = 0;
  while(n > 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

int main() {
  while(true) {
    int number;
    std::cin >> number;
    if(number == 0) {
      return 0;
    }
    
    int numberSum = digitSum(number);
    
    for(int p = 11;; ++p) {
      if(digitSum(number * p) == numberSum) {
        std::cout << p << std::endl;
        break;
      }
    }
  }
}
