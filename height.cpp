#include <iostream>
#include <algorithm>

int numbers[20];

int insertionSort() {
  int steps = 0;
  for(int i = 1; i < 20; ++i) {
    int ii = i;
    
    while(ii != 0 && numbers[ii - 1] > numbers[ii]) {
      std::swap(numbers[ii], numbers[ii - 1]);
      --ii;
    }
    steps += i - ii;
  }

  return steps;
}

int main() {
  int cases;
  std::cin >> cases;
  
  for (int c = 0; c < cases; ++c) {
    int set;
    std::cin >> set;
    
    for (int i = 0; i < 20; ++i) {
      std::cin >> numbers[i];
    }
    std::cout << set << " " << insertionSort() << std::endl;
  }
}
