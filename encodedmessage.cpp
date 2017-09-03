#include <iostream>
#include <cmath>

int main() {
    int cases;
    std::cin >> cases;
    
    for(int c = 0; c < cases; ++c) {
        std::string msg;
        std::cin >> msg;
        
        int length = sqrt(msg.length());
        
        for(int x = length - 1; x > -1; --x)
        for(int y = 0; y < length; ++y) {
            std::cout << msg[y * length + x];
        }
        std::cout << std::endl;
    }
}
