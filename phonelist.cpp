#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> numbers;
  
bool subset(const std::string& a, const std::string& b) {
  int len = std::min(a.length(), b.length());
  
  for(int i = len - 1; i > -1; --i) {
    if(a[i] != b[i]) {
      return false;
    }
  }
  return true;
}
  
void check() {
  for(int i = 1; i < numbers.size(); ++i) {
    if(subset(numbers[i - 1], numbers[i])) {
      std::cout << "NO" << std::endl;
      return;
    }
  }
  std::cout << "YES" << std::endl; 
}
  
int main() {
  int cases;
  std::cin >> cases;
  
  for(int c = 0; c < cases; ++c) {
    int count;
    std::cin >> count;
    numbers.resize(count);
    
    for(int i = 0; i < count; ++i) {
      std::cin >> numbers[i];
    }
    
    std::sort(std::begin(numbers), std::end(numbers));
    check();
  }
}
