#include <map>
#include <set>
#include <string>
#include <iostream>

int main() {
  std::map<std::string, int> wrongs;
  std::set<std::string> correctProblems;
  
  int total = 0;
  
  while(true) {
    int time;
    std::cin >> time;
    
    if(time == -1) {
      break;
    }
    std::string name;
    std::cin >> name;
    
    std::string result;
    std::cin >> result;
    
    if(result == "right") {
      correctProblems.insert(name);
      auto it = wrongs.find(name);
      if (it != wrongs.end()) {
        total += time + (wrongs[name] * 20);
      }
      else {
        total += time;
      }
    } else {
      int wrongsDone = 1;
      
      auto it = wrongs.find(name);
      if (it != wrongs.end()) {
        wrongsDone += wrongs[name];
      }
      
      wrongs[name] = wrongsDone;
    }
  }
  std::cout << correctProblems.size() <<  " " << total << std::endl;
}
