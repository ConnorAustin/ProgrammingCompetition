#include <iostream>

int main() {
  int hour, minutes;
  std::cin >> hour >> minutes;
  
  if(minutes < 45) {
    hour = (23 + hour) % 24;
  }
  
  minutes = (15 + minutes) % 60;
  std::cout << hour << " " << minutes << std::endl;
}
