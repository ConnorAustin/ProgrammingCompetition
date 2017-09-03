#include <iostream>
#include <vector>
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

int main() {
  int count;
  std::cin >> count;
  
  std::string junk;
  std::getline(std::cin, junk);
  
  for(int i = 0; i < count; ++i) {
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> data = split(line, ' ');
    
    int postSecYear = stoi(split(data[1], '/')[0]);
    int yearBorn = stoi(split(data[2], '/')[0]);
    int classesCompleted = stoi(data[3]);
    std::string state = "";
    if(postSecYear >= 2010) {
      state = "eligible";
    } else if(yearBorn >= 1991) {
      state = "eligible";
    } else if (classesCompleted > 40) {
      state = "ineligible";
    } else {
      state = "coach petitions";
    }
    std::cout << data[0] << " " << state << std::endl;
  }
}
