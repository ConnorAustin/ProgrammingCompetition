#include <iostream>
#include <set>

int main() {
  int cases;
  std::cin >> cases;
  
  for (int c = 0; c < cases; ++c) {
    std::set<std::string> places;

    int placeCount;
    std::cin >> placeCount;
    
    std::string place;
    std::getline(std::cin, place); // Read junk line
    
    for (int p = 0; p < placeCount; ++p) {
      std::getline(std::cin, place);
      places.insert(place);
    }
    std::cout << places.size() << std::endl;
  }
}
