#include <iostream>

static int set[1000000];

inline int find(int* a, int minI, int size, int val) {
  int maxI = size;
  
  while(minI < maxI) {
    int midPoint = (minI + maxI) / 2;
    int v = a[midPoint];
    if(v == val) {
      return midPoint;
    }
    if(v < val) {
      minI = midPoint + 1;
    } else {
      maxI = midPoint;
    }
  }
  return -1;
}
  
int main() {
  while (true) {
    int arrCount = 0;
    
    int count1; 
    std::cin >> count1;
    
    int count2;
    std::cin >> count2;
    
    int same = 0;
    int index = 0;
    
    if (count1 == 0 && count2 == 0) {
      break;
    }
    
    for (int c = 0; c < count1; ++c) {
      std::cin >> set[arrCount++];
    }
    
    for (int c = 0; c < count2; ++c) {
      int val;
      std::cin >> val;
      
      int i = find(set, index, arrCount, val); 
      if(i != -1) {
        index  = i;
        ++same;
      }
    }
    std::cout << same << std::endl;
  }
  return 0;
}
