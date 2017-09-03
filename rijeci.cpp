#include <iostream>

int fibVals[46];

int fib(int f) {
  if(f == 0) {
    return 0;
  }
  if(f == 1) {
    return 1;
  }
  if(fibVals[f] == -1) {
    int result = fib(f - 1) + fib(f - 2);
    fibVals[f] = result;
    return result;
  }
  return fibVals[f];
}

int main() {
  int presses;
  std::cin >> presses;
  
  for(int i = 0; i < 46; ++i) {
    fibVals[i] = -1;
  }
  
  std::cout << fib(presses - 1) << " " << fib(presses) << std::endl;
}
