#include <iostream>

int main() {
  std::string line;
  std::getline(std::cin, line);
  
  std::string out;
  
  for(int i = 0; i < line.length(); ++i) {
    char curChar = line[i];
    while(i + 1 < line.length() && curChar == line[i + 1]) {
      ++i;
    }
    out += curChar;
  }
  std::cout << out << std::endl;
}
