#include <iostream>
#include <vector>
#include <cstring>

int wins = 0;
int games = 0;
int draws = 0;
int losses = 0;
int score = 0;

inline bool validate() {
  return (games < 101 && wins > -1 && losses > -1 && score > -1 && draws > -1 && games == wins + draws + losses && score == 3 * wins + draws);
}

int main() {
  std::cin.sync_with_stdio(false);  
  std::cout.sync_with_stdio(false);
  
  int teams;
  std::cin >> teams;
  
  // wins:   1
  // draws:  2
  // losses: 4
  // score:  8
  // game:  16
  const void *const jmpTable[] = { &&done, &&w, &&d, &&wd, &&l, &&wl, &&dl, &&wdl, &&s, &&ws, &&ds, &&wds, &&ls, &&wls, &&dls, &&wdls, &&g, &&gw, &&gd, &&gwd, &&gl, &&gwl, &&gdl, &&gwdl, &&gs, &&gws, &&gds, &&wgds, &&gls, &&gwls, &&gdls };
  
  std::string str;
  for(int t = 0; t < teams; ++t) {
    int jmpTo = 0;
    
    // games
    std::cin >> str;
    if(str == "?") {
      jmpTo += 16;
    } else {
      games = stoi(str);
    }
    
    // wins
    std::cin >> str;
    if(str == "?") {
      jmpTo += 1;
    } else {
      wins = stoi(str);
    }
    
    // draws
    std::cin >> str;
    if(str == "?") {
      jmpTo += 2;
    } else {
      draws = stoi(str);
    }
    
    // losses
    std::cin >> str;
    if(str == "?") {
      jmpTo += 4;
    } else {
      losses = stoi(str);
    }
    
    // score
    std::cin >> str;
    if(str == "?") {
      jmpTo += 8;
    } else {
      score = stoi(str);
    }
    
    goto *jmpTable[jmpTo];
    
    g: {
      games = wins + draws + losses;
      goto done;
    }
    
    w: {
      wins = games - draws - losses;
      goto done;
    }
    
    d: {
      draws = games - losses - wins;
      goto done;
    }
    
    l: {
      losses = games - draws - wins;
      goto done;
    }
    
    s: {
      score = 3 * wins + draws;
      goto done;
    }
    
    gw: {
      wins = (score - draws) / 3;
      games = wins + draws + losses;
      goto done;
    }
    
    gd: {
      draws = score - 3 * wins;
      games = wins + draws + losses;
      goto done;
    }
    
    gl: {
      for(games = 0;; ++games) {
        losses = games - wins - draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gwd: {
      for(games = 0;games < 101; ++games) {
        wins = (score + losses - games) / 2;
        draws = games - wins - losses;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gwl: {
      for(games = 0; games < 101; ++games) {
        wins = (score - draws) / 3;
        losses = games - wins - draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gdl: {
      for(games = 0; games < 101; ++games) {
        draws = score - 3 * wins;
        losses = games - wins - draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gws: {
      for(games = 0; games < 101; ++games) {
        wins = games - losses - draws;
        score = 3 * wins + draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gds: {
      for(games = 0; games < 101; ++games) {
        draws = games - wins - losses;
        score = 3 * wins + draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gls: {
      for(games = 0; games < 101; ++games) {
        losses = games - wins - draws;
        score = 3 * wins + draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    wds: {
      for(wins = 0;; ++wins) {
        draws = games - wins - losses;
        score = 3 * wins + draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    wls: {
      for(wins = 0;; ++wins) {
        score = 3 * wins + draws;
        losses = games - wins - draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    wdl: {
      for(wins = 0;; ++wins) {
        draws = score - 3 * wins;
        losses = games - wins - draws;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    dls: {
      for(score = 0;; ++score) {
        draws = score - 3 * wins;
        losses = games - draws - wins;
        if(validate()) {
          break;
        }
      }
      goto done;
    }
    
    gs: {
      score = draws + 3 * wins;
      games = wins + draws + losses;
      goto done;
    }
    
    wd: {
      wins = (score + losses - games) / 2;
      draws = games - wins - losses;
      goto done;
    }
    
    wl: {
      wins = (score - draws) / 3;
      losses = games - wins - draws;
      goto done;
    }
    
    ws: {
      wins = games - losses - draws;
      score = 3 * wins + draws;
      goto done;
    }
    
    dl: {
      draws = score - 3 * wins;
      losses = games - wins - draws;
      goto done;
    }
    
    ds: {
      draws = games - wins - losses;
      score = 3 * wins + draws;
      goto done;
    }
    
    ls: {
      losses = games - wins - draws;
      score = 3 * wins + draws;
      goto done;
    }
    
    wdls: {
      for(wins = 0;; ++wins) {
        for(draws = 0; draws <= games - wins; ++draws) {
          score = 3 * wins + draws;
          losses = games - wins - draws;
          if(validate()) {
            goto done;
          }
        }
      }
      goto done;
    }
    
    gwdl: {
      for(wins = 0;; ++wins) {
        for(losses = 0; losses <= 100 - wins; ++losses) {
          draws = score - 3 * wins;
          games = wins + draws + losses;
          if(validate()) {
            goto done;
          }
        }
      }
      goto done;
    }
    
    gwls: {
      for(wins = 0;; ++wins) {
        for(losses = 0; losses <= 100 - wins - draws; ++losses) {
          score = 3 * wins + draws;
          games = wins + draws + losses;
          if(validate()) {
            goto done;
          }
        }
      }
      goto done;
    }
    
    gdls: {
      for(draws = 0;; ++draws) {
        for(losses = 0; losses <= 100 - draws - wins; ++losses) {
          score = 3 * wins + draws;
          games = wins + draws + losses;
          if(validate()) {
            goto done;
          }
        }
      }
      goto done;
    }
    
    wgds: {
      for(wins = 0;; ++wins) {
        for(draws = 0; draws <= 100 - wins - losses; ++draws) {
          score = 3 * wins + draws;
          games = wins + draws + losses;
          if(validate()) {
            goto done;
          }
        }
      }
      goto done;
    }
    done:
    std::cout << games << ' ' << wins << ' ' << draws << ' ' << losses << ' ' << score << std::endl;
  }
}
