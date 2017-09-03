#include <iostream>

int main() {
  while(true) {
    int samples;
    std::cin >> samples;
    
    if(samples == -1) {
      break;
    }
    
    int prevTime = 0;
    int distance = 0;
    for(int s = 0; s < samples; ++s) {
      int speed;
      std::cin >> speed;
      
      int time;
      std::cin >> time;
      
      int dt = time - prevTime;
      distance += speed * dt;
      prevTime = time;
    }
    
    std::cout << distance << " miles" << std::endl;
  }
}
