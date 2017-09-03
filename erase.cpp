#include <iostream>
#include <algorithm>

void replace(std::string& str, char a, char b) {
  std::replace_if(std::begin(str), std::end(str), [a](const char& c) {
    return c == a;
  }, b);
}

int main() {
  int times;
  std::cin >> times;
  
  std::string x, y;
  std::getline(std::cin, x); // read junk line
  std::getline(std::cin, x);
  std::getline(std::cin, y);
  
  std::string z(y);
  replace(z, '0', '2');
  replace(z, '1', '0');
  replace(z, '2', '1');
  
  if(times % 2 == 0 && x == y) {
    std::cout << "Deletion succeeded" << std::endl;
  } else if(times % 2 == 1 && x == z) {
    std::cout << "Deletion succeeded" << std::endl;  
  } else {
    std::cout << "Deletion failed" << std::endl;
  }
}
