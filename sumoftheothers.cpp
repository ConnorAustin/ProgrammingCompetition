#include <iostream>
#include <sstream>
#include <numeric>

int digits[30];

int main() {
    std::string line;
    while(!std::cin.eof()) {
        std::getline(std::cin, line);
        
        std::stringstream line_stream(line);
        int digits_len = 0;
        for(; !line_stream.eof(); ++digits_len) {
            line_stream >> digits[digits_len];
        }
        
        int sum = std::accumulate(std::begin(digits), std::begin(digits) + digits_len, 0);
        for(int i = 0; i < digits_len; ++i) {
            if(sum - digits[i] == digits[i]) {
                std::cout << digits[i] << std::endl;
                break;
            }
        }
    }
}