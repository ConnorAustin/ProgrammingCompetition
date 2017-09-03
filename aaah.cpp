#include <iostream>

int main() {
  std::string ah1;
  std::string ah2;
  
  std::getline(std::cin, ah1);
  std::getline(std::cin, ah2);
  
  if(ah1.length() >= ah2.length()) {
    std::cout << "go" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
}
