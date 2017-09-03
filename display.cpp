#include <iostream>

std::string numbers[] = 
{"+---+|   ||   |+   +|   ||   |+---+", // 0
"    +    |    |    +    |    |    +",  // 1
"+---+    |    |+---+|    |    +---+",  // 2
"+---+    |    |+---+    |    |+---+",  // 3
"+   +|   ||   |+---+    |    |    +",  // 4
"+---+|    |    +---+    |    |+---+",  // 5
"+---+|    |    +---+|   ||   |+---+",  // 6
"+---+    |    |    +    |    |    +",  // 7
"+---+|   ||   |+---+|   ||   |+---+",  // 8
"+---+|   ||   |+---+    |    |+---+"}; // 9

int main() {
    while(true) {
        std::string time_str;
        std::cin >> time_str;

        if(time_str == "end") {
            break;
        }
        
        int time[] = {
            time_str[0] - '0',
            time_str[1] - '0',
            time_str[3] - '0',
            time_str[4] - '0',
        };
        
        for(int y = 0; y < 7; ++y) {
            for(int t = 0; t < 4; ++t) {
                if(t == 2) {
                    if(y == 2 || y == 4) {
                        std::cout << "  o  ";
                    } else {
                        std::cout << "     ";
                    }
                } else if(t != 0) {
                    std::cout << "  ";
                }
                std::cout << numbers[time[t]].substr(y * 5, 5);
            }
            
            if(y == 6) {
                std::cout << std::endl << std::endl << std::endl;
            } else {
                std::cout << std::endl;
            }
        }
    }
    
    std::cout << "end" << std::endl;
}
