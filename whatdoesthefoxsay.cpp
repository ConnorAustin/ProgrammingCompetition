#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

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
  int cases;
  std::cin >> cases;
  
  std::string soundsLine;
  std::getline(std::cin, soundsLine); // read junk line
  
  for(int c = 0; c < cases; ++c) {
    std::getline(std::cin, soundsLine);
    
    std::vector<std::string> sounds = split(soundsLine, ' ');
    
    while(true) {
      std::string sentence;
      std::getline(std::cin, sentence);
      if(sentence == "what does the fox say?") {
        break;
      }
      
      auto index = sentence.rfind(" goes ");
      std::string sound = sentence.substr(index + 6, sentence.length() - 1);
      auto it = std::remove(std::begin(sounds), std::end(sounds), sound);
      sounds.resize(std::distance(std::begin(sounds), it));
    }
    
    for(const std::string& str : sounds) {
      std::cout << str << " ";
    }
    std::cout << std::endl;
  }
}
