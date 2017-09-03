#include <iostream>
#include <map>

int main() {
  int cases;
  std::cin >> cases;
  
  for(int c = 0; c < cases; ++c) {
    int guests;
    std::cin >> guests;
    
    std::map<int, int> cards;
    for(int g = 0; g < guests; ++g) {
      int card;
      std::cin >> card;
      
      cards[card] += 1;
    }
    
    for(auto card : cards) {
      if(card.second == 1) {
        std::cout << "Case #" << (c + 1) << ": " << card.first << std::endl;
      }
    }
  }
}
