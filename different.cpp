#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class big {
public:
  long long lo = 0;
  long long hi = 0;
  
  big(std::string num) {
    int place = 1;
    
    for(int i = 0; i < std::min(9, (int)num.length()); ++i) {
      char c = num[num.length() - i - 1];
      lo += (c - '0') * place;
      place *= 10;
    }
    
    place = 1;
    for(int i = 0; i < std::max(0, (int)num.length() - 9); ++i) {
      char c = num[num.length() - i - 10];
      hi += (c - '0') * place;
      place *= 10;
    }
  }
  
  bool smaller(const big& other) {
    if(hi < other.hi) {
      return true;
    }
    if(hi == other.hi) {
      return lo < other.lo;
    }
    return false;
  }
  
  void diff(const big& other) {
    lo -= other.lo;
    if(lo < 0) {
      --hi;
      lo = 1000000000 + lo;
    }
    hi -= other.hi;
  }
  
  void print() {
    if(hi > 0) {
      printf("%lld%09lld\n", hi, lo);
    }
    else {
      std::cout << lo << std::endl;
    }
  }
};

int main() {
  while(true) {
    std::string a, b;
    std::cin >> a >> b;
    if(std::cin.eof()) {
      break;
    }
    
    big x(a);
    big y(b);
    
    if(x.smaller(y)) {
      y.diff(x);
      y.print();
    } else {
      x.diff(y);
      x.print();
    }
  }
}
