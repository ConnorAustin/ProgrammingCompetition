#include <iostream>

int main() {
  int low1, low2, low3, low4;
  int high1, high2, high3, high4;
  
  std::cin >> low1 >> high1 >> low2 >> high2 >> low3 >> high3 >> low4 >> high4;
  
  int gunnar = 0;
  int emma = 0;
  
  for(int d1 = low1; d1 < high1 + 1; ++d1) {
    for(int d2 = low2; d2 < high2 + 1; ++d2) {
      for(int d3 = low3; d3 < high3 + 1; ++d3) {
        for(int d4 = low4; d4 < high4 + 1; ++d4) {
          if(d1 + d2 > d3 + d4) {
            ++gunnar;
          }
          else if(d1 + d2 < d3 + d4) {
            ++emma;
          }
        } 
      } 
    }
  }
  if(gunnar > emma) {
    std::cout << "Gunnar" << std::endl;
  } else if(emma > gunnar) {
    std::cout << "Emma" << std::endl;
  } else {
    std::cout << "Tie" << std::endl;
  }
}
