#include <iostream>

std::string solve(int a, int b, int c) {
  if (a + b == c) {
    return "+";
  } else if (a - b == c) {
    return "-";
  } else if (a * b == c) {
    return "*";
  } else if (b != 0 && a / b == c) {
    return "/";
  }
  return "";
}

int main() {
  int a, b, c;
  std::cin >> a >> b >> c;
  
  std::string op = solve(a, b, c);
  if(op != "") {
    std::cout << a << op << b << '=' << c << std::endl;
  } else {
    std::cout << a << '=' << b << solve(b, c, a) << c << std::endl;
  }
}
