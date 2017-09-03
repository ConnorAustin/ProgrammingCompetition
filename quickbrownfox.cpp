#include <iostream>
#include <string>
#include <algorithm>

int main() {
  int cases;
  std::cin >> cases;
  std::string line;
  std::getline(std::cin, line); // read junk line
    
  for(int c = 0; c < cases; ++c) {
    std::getline(std::cin, line);
    std::transform(std::begin(line), std::end(line), std::begin(line), tolower);
    
    std::sort(std::begin(line), std::end(line));
    
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    
    auto end2 = std::set_difference(std::begin(alphabet), std::end(alphabet), std::begin(line), std::end(line), std::begin(alphabet));
    alphabet.resize(std::distance(std::begin(alphabet), end2));
    
    if(alphabet == "") {
      std::cout << "pangram " << std::endl;
    } else {
      std::cout << "missing " << alphabet << std::endl;
    }
  }
}
