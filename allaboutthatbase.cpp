#include <iostream>
#include <functional>
#include <cstdint>

const std::string bases = "!123456789abcdefghijklmnopqrstuvwxyz0";

using uint64 = uint_least64_t;

uint64 convert_digit(char c) {
  uint64 n = c;
  if(n <= '9') {
    n -= '0';
  } else {
    n += (10 - 'a');
  }
  return n;
}

uint64 min_valid_base(const std::string& num) {
  uint64 base = 0;
  
  for(char c : num) {
    uint64 digitVal = convert_digit(c);
    base = std::max(base, digitVal + 1);
  }
  
  // unary(base 1) breaks this system since it uses 1's
  // like base 2 but just not 0's. what a twerp
  if(base == 2)
    return 1;
    
  return base;
}

uint64 convert(const std::string& num, uint64 base) {
  uint64 result = 0;
  uint64 prevResult = 0;
  
  // special unary case
  if(base == 1) {  
    for(char c : num) {
      if(c != '1') {
        return 0;
      }
      ++result;
    }
    return result;
  }
  
  uint64 place = 1;
  
  for(int c = num.length() - 1; c >= 0; --c) {
    uint64 n = convert_digit(num[c]);
    
    result += n * place;
    place *= base;
    
    // overflow?
    if(prevResult > result) { 
      return 0; // yep, we done messed up
    }
    prevResult = result;
  }
  
  return result;
}

bool try_add(uint64 a, uint64 b, uint64 ans) {
  return (a + b) == ans;
}

bool try_sub(uint64 a, uint64 b, uint64 ans) {
  return (a - b) == ans;
}

bool try_mul(uint64 a, uint64 b, uint64 ans) {
  return (a * b) == ans;
}

bool try_div(uint64 a, uint64 b, uint64 ans) {
  return ans * b == a;
}

int main() {
  uint64 cases;
  std::cin >> cases;
  
  for(uint64 i = 0; i < cases; ++i) {
    std::string a, b, equals, ans;
    char op;
    std::cin >> a >> op >> b >> equals >> ans;
    
    std::function<bool(uint64, uint64, uint64)> mathOpFunc;
    
    // Parse operation
    switch(op) {
      case '+': mathOpFunc = try_add; break;
      case '-': mathOpFunc = try_sub; break;
      case '*': mathOpFunc = try_mul; break;
      default:  mathOpFunc = try_div; break;
    }
    
    bool foundOneBase = false;
    
    uint64 minBase = std::max(std::max(min_valid_base(a), min_valid_base(b)), min_valid_base(ans));
    if(minBase == 0) {
      std::cout << "invalid" << std::endl;
      continue;
    }
    for(uint64 base = minBase; base < 37; ++base) {
      uint64 ac   = convert(a, base);
      uint64 bc   = convert(b, base);
      uint64 ansc = convert(ans, base);
      
      if(ac == 0 || bc == 0 || ansc == 0) {
        continue;
      }
      
      if(mathOpFunc(ac, bc, ansc)) {
        std::cout << bases[base];
        foundOneBase = true;
      }
    }
    if(!foundOneBase) {
      std::cout << "invalid";
    }
    std::cout << std::endl;
  }
}
