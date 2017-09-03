#include <iostream>
#include <vector>
#include <string>
#include <map>

const std::map<std::string, char> map = {
  {"**** ** ** ****", '0'},
  {"  *  *  *  *  *", '1'},
  {"***  *****  ***", '2'},
  {"***  ****  ****", '3'},
  {"* ** ****  *  *", '4'},
  {"****  ***  ****", '5'},
  {"****  **** ****", '6'},
  {"***  *  *  *  *", '7'},
  {"**** ***** ****", '8'},
  {"**** ****  ****", '9'}
};

std::vector<std::string> numbers;

int main() {
  int len = 0;
  char buf[3];
  
  for(int i = 0; i < 5; ++i) {
    std::string line;
    std::getline(std::cin, line);
    if(i == 0) {
      len = (line.length() + 1) / 4;
      numbers.resize(len);
      
      for(int j = 0; j < len; ++j) {
        numbers[j] = std::string();
      }
    }
    
    for(int j = 0; j < len; ++j) {
      numbers[j] += line.substr(j * 4, 3);;
    }
  }
  
  std::string bombNumber;
  
  for(int i = 0; i < len; ++i) {
    auto it = map.find(numbers[i]);
    if(it == std::end(map)) {
      std::cout << "BOOM!!" << std::endl;
      return 0;
    }
    bombNumber += it->second;
  }
  
  try {
    if(stoi(bombNumber) % 6 == 0) {
      std::cout << "BEER!!" << std::endl;
      return 0;
    }
  }
  catch(std::exception e) { }
  std::cout << "BOOM!!" << std::endl;
}
