#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int cases;
  std::cin >> cases;
  
  for (int c = 0; c < cases; ++c) {
    int ropes;
    std::cin >> ropes;
    
    std::vector<int> redRopes;
    std::vector<int> blueRopes;

    for (int r = 0; r < ropes; ++r) {
      std::string rope;
      std::cin >> rope;
      
      int ropeLength = stoi(rope.substr(0, rope.length() - 1));

      if (rope[rope.length() - 1] == 'R') {
        redRopes.push_back(ropeLength);
      } else {
        blueRopes.push_back(ropeLength);
      }
    }
    
    std::sort(std::begin(redRopes), std::end(redRopes));
    std::sort(std::begin(blueRopes), std::end(blueRopes));
    
    std::reverse(std::begin(blueRopes), std::end(blueRopes));
    std::reverse(std::begin(redRopes), std::end(redRopes));
    
    int loopRopeCount = std::min(redRopes.size(), blueRopes.size());
    int loopLength = 0;

    for (int i = 0; i < loopRopeCount; ++i) {
      loopLength += redRopes[i] + blueRopes[i] - 2;
    }
    
    std::cout << "Case #" << (c + 1) << ": " << loopLength << std::endl;
  }
}
