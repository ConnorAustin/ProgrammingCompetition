#include <iostream>
#include <vector>

int main() {
  int cases;
  std::cin >> cases;
  
  for(int c = 0; c < cases; ++c) {
     int people, issues;
     std::cin >> people >> issues;
     
     std::vector<int> pole;
     pole.resize(issues);
     for(int p = 0; p < people; ++p) {
       std::string belief;
       std::cin >> belief;
       for(int i = 0; i < issues; ++i) {
         pole[i] += belief[i] == '1' ? 1 : -1;
       }
     }
     for(int i = 0; i < issues; ++i) {
       if(pole[i] > 0) {
         std::cout << '1';
       } else {
         std::cout << '0';
       }
     }
     std::cout << std::endl;
  }
}
