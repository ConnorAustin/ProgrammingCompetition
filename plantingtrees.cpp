#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int count;
  std::cin >> count;
  
  std::vector<int> seeds;
  seeds.resize(count);

  for (int i = 0; i < count; ++i) {
    std::cin >> seeds[i];
  }
  std::sort(std::begin(seeds), std::end(seeds));

  int maxTime = 0;
  for (int i = 0; i < count; ++i) {
    int time = seeds[count - i - 1] + i + 1;
    maxTime = std::max(maxTime, time);
  }
  
  std::cout << (maxTime + 1) << std::endl;
}
