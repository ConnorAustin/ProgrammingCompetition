#include <iostream>
#include <algorithm>
#include <array>

std::array<char, 28> table{{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 
                             'H', 'I', 'J', 'K', 'L', 'M', 'N',
                             'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                             'V', 'W', 'X', 'Y', 'Z', '_', '.' }};
                                              
int main() {
  while (true) {
    int rotAmt;
    std::cin >> rotAmt;
    if (rotAmt == 0) {
      return 0;
    }

    std::string str;
    std::cin >> str;
    std::reverse(std::begin(str), std::end(str));
    
    for(int i = 0; i < str.length(); ++i) {
      char c = str[i];
      
      auto it = std::find(std::begin(table), std::end(table), c);
      if(it != std::end(table)) {
        int index = std::distance(std::begin(table), it);
        str[i] = table[(index + rotAmt) % 28];
      }
    }
    std::cout << str << std::endl;
  }
}
