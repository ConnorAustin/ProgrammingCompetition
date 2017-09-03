#include <iostream>

char frameChar(int x, int y) {
  if((x + y) % 2 == 0) {
    return '#';
  }
  return '.';
}

int main() {
  int w, h;
  std::cin >> h >> w;
  
  int u, l, r, d;
  std::cin >> u >> l >> r >> d;
  
  std::string word;
  std::getline(std::cin, word); // remove junk newline
  
  for(int y = 0; y < u; ++y) {
    for(int x = 0; x < w + l + r; ++x) {
      std::cout << frameChar(x, y);
    }
    std::cout << std::endl;
  }
  
  for(int y = 0; y < h; ++y) {
    for(int x = 0; x < l; ++x) {
      std::cout << frameChar(x, y + u);
    }
    std::getline(std::cin, word);
    std::cout << word;
    
    for(int x = 0; x < r; ++x) {
      std::cout << frameChar(l + w + x, y + u);
    }
    
    std::cout << std::endl;
  }
  for(int y = 0; y < d; ++y) {
    for(int x = 0; x < l + w + r; ++x) {
      std::cout << frameChar(x, u + h + y);
    }
    std::cout << std::endl;
  }
}
