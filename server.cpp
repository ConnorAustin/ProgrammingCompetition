#include <iostream>

int main() {
  int tasks;
  std::cin >> tasks;
  
  int timeout;
  std::cin >> timeout;
  
  int tasksDone = 0;
  int time = 0;
  for(int t = 0; t < tasks; ++t) {
    int tim;
    std::cin >> tim;
    
    time += tim;
    if(time > timeout) {
      break;
    }
    ++tasksDone;
  }
  std::cout << tasksDone << std::endl;
}
