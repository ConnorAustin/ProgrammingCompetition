#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  std::cin.sync_with_stdio(false);
  
  while(true) {
    int n;
    std::cin >> n;
    if(n == 0) {
      return 0;
    }
    
    std::vector<int> l1;
    std::vector<int> l1_sorted;
    l1.resize(n);
    l1_sorted.resize(n);
    for(int i = 0; i < n; ++i) {
      std::cin >> l1[i];
      l1_sorted[i] = l1[i];
    }
    
    std::vector<int> l2;
    std::vector<int> l2_sorted;
    l2.resize(n);
    l2_sorted.resize(n);
    for(int i = 0; i < n; ++i) {
      std::cin >> l2[i];
      l2_sorted[i] = l2[i];
    }
    
    std::sort(std::begin(l1_sorted), std::end(l1_sorted));
    std::sort(std::begin(l2_sorted), std::end(l2_sorted));
    
    for(int i : l1) {
      auto it = std::lower_bound(std::begin(l1_sorted), std::end(l1_sorted), i);
      int index = std::distance(std::begin(l1_sorted), it);
      std::cout << l2_sorted[index] << std::endl;
    }
    std::cout << std::endl;
  }
}
