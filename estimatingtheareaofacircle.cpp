#include <iostream>
#include <cmath>

int main() {  
  while(true) {
    double r;
    std::cin >> r;
    
    if(r == 0) {
      break;
    }
    
    double m;
    std::cin >> m;
    
    double c;
    std::cin >> c;
    
    double a1 = r * r * M_PI;
    double a2 = (4 * r * r * c) / m;
    
    std::cout << a1 << " " << a2 << std::endl;
  }
}
