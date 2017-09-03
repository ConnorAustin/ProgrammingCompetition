#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

int main() {
  std::vector<std::string> lines;
  size_t maxLineLen = 0;
  
  std::string line;
  while (std::getline(std::cin, line)) {
    lines.push_back(line);
  }
  
  for(std::string line : lines) {
    maxLineLen = std::max(maxLineLen, line.length());
  }
  
  if(lines.size() > 0) {
    lines.erase(lines.end() - 1);
  }
  
  int result = 0;
  for(std::string line : lines) {
    int nm = maxLineLen - line.length();
    result += nm * nm;
  }
  
  std::cout << result << std::endl;
}
