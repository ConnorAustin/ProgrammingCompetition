#include <iostream>

int main() {
  int numbers;
  std::cin >> numbers;
  
  for(int n = 0; n < numbers; ++n) {
    int x;
    
    std::cin >> x;
    int b = x & 0x1;
    int res = 0;
    res += b;
    for(int p = 1; p < 8; ++p) {
      if((x & (1 << p)) == 0) {
        res += b << p;
      } else {
        res += (!b << p) & (1 << p);
        b = !b;
      }
    }
    std::cout << res << std::endl;
  }
}
