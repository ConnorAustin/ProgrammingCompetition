#include <iostream>

int main() {
    std::cout.sync_with_stdio(false);
    std::cin.sync_with_stdio(false);
    
    int cases = 1;
    while(true) {
        std::string line;
        std::getline(std::cin, line);
        
        if(line == "END") {
            break;
        }

        int black_index = -1;
        int dist = -1;
        for(int c = 0; c < line.length(); ++c) {
            if(line[c] == '*') {
                if(black_index == -1) {
                    black_index = c;
                } else {
                    int d = c - black_index;
                    if(dist == -1) {
                        dist = d;
                    } else if(dist != d) {
                        std::cout << cases << " NOT EVEN" << std::endl;
                        goto done;
                    }
                    black_index = c;
                }
            }
        }
        std::cout << cases << " EVEN" << std::endl;
        done:
        ++cases;
    }
}
