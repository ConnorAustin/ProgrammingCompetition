#include <iostream>
#include <vector>
#include <algorithm>

int main() {
  int count;
  std::cin >> count;
  
  std::vector<std::string> names;

  for (int i = 0; i < count; ++i) {
    std::string name;
    std::cin >> name;
    names.push_back(name);
  }
  
  std::vector<std::string> sorted(names);
  std::sort(std::begin(sorted), std::end(sorted));
  
  std::vector<std::string> reverse(sorted);
  std::reverse(std::begin(reverse), std::end(reverse));

  if (sorted == names) {
    std::cout << "INCREASING" << std::endl;
  } else if (reverse  == names) {
    std::cout << "DECREASING" << std::endl;
  } else {
    std::cout << "NEITHER" << std::endl;
  }
}
