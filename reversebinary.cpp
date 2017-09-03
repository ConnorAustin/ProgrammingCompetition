#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

std::string removeLeadingZeros(const std::string& str) {
  std::string s;
  bool test = true;
  for(auto& c : str) {
    if(test) {
      if(c == '1') {
        test = false;
        s += c;
      }
    } else {
      s += c;
    }
  }
  return s;
}

int main() {
  int number;
  std::cin >> number;
  
  std::string str = std::bitset<32>(number).to_string();
  str = removeLeadingZeros(str);
  
  std::reverse(std::begin(str), std::end(str));
  
  auto a = std::bitset<32>(str).to_ulong();
  
  std::cout << a << std::endl;
}
