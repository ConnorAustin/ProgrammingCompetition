#include <iostream>

std::string block[7];

char get(int x, int y) {
  if(x >= 0 && x < 7 && y >= 0 && y < 7) {
    return block[x][y];
  }
  return '!';
}
  
int main() {
  for (int i = 0; i < 7; ++i) {
    std::getline(std::cin, block[i]);
  }
  
  int moves = 0;
  
  for(int y = 0; y < 7; ++y) {
    for(int x = 0; x < 7; ++x) {
      if(block[x][y] != 'o') {
        continue;
      }
      
      if(get(x + 1, y) == 'o' && get(x + 2, y) == '.') {
        ++moves; 
      }
      
      if(get(x - 1, y) == 'o' && get(x - 2, y) == '.') {
        ++moves;
      }
      
      if(get(x, y + 1) == 'o' && get(x, y + 2) == '.') {
        ++moves;
      }
      
      if(get(x, y - 1) == 'o' && get(x, y - 2) == '.') {
        ++moves;
      }
    }
  }
  std::cout << moves << std::endl;
}
