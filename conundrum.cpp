#include <iostream>
#include <algorithm>

const std::string name = "per";

int main() {
  std::string text;
  std::cin >> text;
  std::transform(std::begin(text), std::end(text), std::begin(text), tolower);
  
  int letter = 0;
  int days = 0;
  for(char c : text) {
    if(c != name[letter]) {
      ++days;
    }
    letter = (letter + 1) % 3;
  }
  std::cout << days << std::endl;
}
