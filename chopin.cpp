#include <iostream>
#include <map>

int main() {
  int c = 1;
  
  while (true) {
    std::string note;
    std::cin >> note;
    
    std::string tonality;
    std::cin >> tonality;
    
    if(std::cin.eof()) {
      return 0;
    }
    
    std::map<std::string, std::string> map = {
      {"A#", "Bb"},
      {"Bb", "A#"},
      {"C#", "Db"},
      {"Db", "C#"},    
      {"D#", "Eb"},
      {"Eb", "D#"},
      {"F#", "Gb"},
      {"Gb", "F#"},
      {"G#", "Ab"},
      {"Ab", "G#"}
    };
    
    std::cout << "Case " << c << ": ";
    
    std::string alt;
    
    auto it = map.find(note);
    if(it != map.end()) {
      std::cout << it->second << " " << tonality << std::endl;
    } else {
      std::cout << "UNIQUE" << std::endl;
    }
    
    ++c;
  }
}
