#include <iostream>
#include <sstream>
#include <numeric>

char characters[] = {'.', '#'};

int main() {
    bool starting = true;
    int scanlines;
    while(std::cin >> scanlines, scanlines != 0) {
        if(!starting) {
            std::cout << std::endl;
        }
        starting = false;
        
        std::string line;
        std::getline(std::cin, line); // read junk newline
        
        int prev_sum = -1;
        bool error = false;
        
        for(int scanline = 0; scanline < scanlines; ++scanline) {    
            std::getline(std::cin, line);
            std::stringstream sstream(std::move(line));
            
            char starting_char;
            sstream >> starting_char;
            int char_offset = starting_char == '.' ? 0 : 1;
            
            int sum = 0;
            int index = 0;
            while(!sstream.eof()) {
                int run = 0;
                sstream >> run;
                sum += run;
                
                for(int c = 0; c < run; ++c) {
                    std::cout << characters[(index + char_offset) % 2];
                }
                ++index;
            }
            
            if(prev_sum != -1 && sum != prev_sum) {
                error = true;
            }
            prev_sum = sum;
            std::cout << std::endl;
        }
        if(error) {
            std::cout << "Error decoding image" << std::endl;
        }
    }
}