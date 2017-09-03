#include <iostream>

int main() {
  std::string a, b;
  std::cin >> a >> b;
  
  // special case when the virus did nothing
  if(a == b) {
    std::cout << "0" << std::endl;
    return 0;
  }
  
  // find left side of the virus
  int left = 0;
  while(a[left] == b[left] && 
       (left != a.length() || left != a.length())) {
    ++left;
  }
  
  // find right side of the virus
  int right = 0;
  while(a[a.length() - right - 1] == b[b.length() - right - 1] &&
   right + left != a.length() && right + left != b.length()) {
    ++right;
  }
  
  std::cout << b.length() - right - left << std::endl;
}
