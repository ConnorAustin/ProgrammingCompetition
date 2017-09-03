#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

std::vector<std::string> split(const std::string& str, char delim) {
  std::vector<std::string> result;
  std::stringstream ss(str);
  
  std::string next;
  while(!ss.eof()) {
    std::getline(ss, next, delim);
    result.push_back(next);
  }
  
  return result;
}

void replace(std::string& str, const std::string& in, const std::string& out) {
  size_t i = str.find(in);
  while(i != std::string::npos) {
    str.replace(i, in.length(), out);
    i = str.find(in, i + out.length());
  }
}

int main() {
  std::string str;
  std::getline(std::cin, str);
  
  for(std::string c : split(str, ' ')) {    
    replace(c, "apa", "a");
    replace(c, "epe", "e");
    replace(c, "ipi", "i");
    replace(c, "opo", "o");
    replace(c, "upu", "u");
    std::cout << c << " ";
  }

  std::cout << std::endl;
}
