#include <iostream>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>

#define byte uint8_t
int pair[826]; // 0001 10011 1001 is the max value, 25 << 5 + 25 = 825
std::string line;

int main() {
    std::cin.sync_with_stdio(false);
    while(true) {
        memset(pair, 0, sizeof(pair));
        
        int found = 0;
        std::getline(std::cin, line);
        if(std::cin.eof()) {
            return 0;
        }
        
        for(int i = 0; i < line.length() - 1; ++i) {
            byte c1 = line[i];
            byte c2 = line[i + 1];
            
            if(c1 >= 'a' && c1 <= 'z') {
                c1 -= 'a';
            } else if(c1 >= 'A' && c1 <= 'Z') {
                c1 -= 'A';
            } else {
                continue;
            }
            
            if(c2 >= 'a' && c2 <= 'z') {
                c2 -= 'a';
            } else if(c2 >= 'A' && c2 <= 'Z') {
                c2 -= 'A';
            } else {
                ++i;
                continue;
            }
            
            if(c1 < c2) {
                std::swap(c1, c2);
            }
            
            int number = (c1 << 5) | c2;
            if(++pair[number] == 1) {
                ++found;
            }
        }
        printf("%d\n", found);
    }
}
