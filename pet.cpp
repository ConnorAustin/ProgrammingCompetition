#include <iostream>

int main() {
  int bestContestant = 0;
  int bestScore = -1;
  
  for (int i = 0; i < 5; ++i) {
    int total = 0;
    for(int j = 0; j < 4; ++j) {
      int score;
      std::cin >> score;
      total += score;
    }
    if (total > bestScore) {
      bestScore = total;
      bestContestant = i;
    }
  }
  std::cout << (bestContestant + 1) << " " << bestScore << std::endl;
}
