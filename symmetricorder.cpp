#include <iostream>
#include <algorithm>
#include <vector>

int main() {
  int set = 1;

  while (true) {
    int count;
    std::cin >> count;

    if (count == 0) {
      break;
    }
    
    std::vector<std::string> names1;
    std::vector<std::string> names2;

    for (int i = 0; i < count; ++i) {
      std::string name;
      std::cin >> name;
      
      if (i % 2 == 1) {  
        names2.push_back(name);
      } else {
        names1.push_back(name);
      }
    }
    
    std::sort(std::begin(names1), std::end(names1), [](const std::string& a, const std::string& b) {
      return a.length() < b.length();
    });
    
    std::sort(std::begin(names2), std::end(names2), [](const std::string& a, const std::string& b) {
      return a.length() < b.length();
    });
    
    std::vector<std::string> rev2(names2);
    std::reverse(std::begin(rev2), std::end(rev2));

    std::cout << "SET " << set << std::endl;
    for (std::string name : names1) {
      std::cout << name << std::endl;
    }

    for (std::string name : rev2) {
      std::cout << name << std::endl;
    }
    ++set;
  }
}
