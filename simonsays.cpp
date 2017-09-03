#include <iostream>
#include <string>

int main() {
  int count;
  std::cin >> count;
  std::string str;
  std::getline(std::cin, str);
  
  for(int i = 0; i < count; ++i) {    
    std::string str;
    std::getline(std::cin, str);
    std::string start = str.substr(0, 10);
    
    if(start == "Simon says") {
      std::cout << str.substr(11, std::string::npos) << std::endl;
    }
  }
}
