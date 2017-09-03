#include <iostream>
#include <string>

int main() {
  std::string line;
  std::getline(std::cin, line);
  
  int whitespace = 0;
  int lower = 0;
  int upper = 0;
  int symbol = 0;

  for (char c : line) {
    if (c == '_') {
      ++whitespace;
    } else if (c >= 'a' && c <= 'z') {
      ++lower;
    } else if (c >= 'A' && c <= 'Z') {
      ++upper;
    } else {
      ++symbol;
    }
  }
  
  std::cout << 
  ((double) whitespace / (double) line.length()) << std::endl <<
  ((double) lower      / (double) line.length()) << std::endl <<
  ((double) upper      / (double) line.length()) << std::endl <<
  ((double) symbol     / (double) line.length()) << std::endl;
}
