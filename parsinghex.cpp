#include <iostream>

using ull = unsigned long long;

ull to_decimal(const std::string& hex_str) {
    ull ans = 0;
    ull base = 1;
    
    for(int c = hex_str.length() - 1; c > 1; --c) {
        char d = hex_str[c];
        if(d >= '0' && d <= '9') {
            ans += (d - '0') * base;
        }
        else if(d >= 'a' && d <= 'f') {
            ans += (d - 'a' + 10) * base;
        }
        else if(d >= 'A' && d <= 'F') {
            ans += (d - 'A' + 10) * base;
        }
        
        base *= 16;
    }
    return ans;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    while(true) {
        std::string line;
        std::getline(std::cin, line);
        if(std::cin.eof()) {
            break;
        }
        for(int c = 0; c < line.length() - 2; ++c) {
            if(line[c] == '0' && (line[c + 1] == 'x' || line[c + 1] == 'X')) {
                std::string hex_str = "0";
                hex_str += line[c + 1];
                
                for(c += 2; c < line.length(); ++c) {
                    char d = line[c];
                    if((d >= '0' && d <= '9') || (d >= 'a' && d <= 'f') || (d >= 'A' && d <= 'F')) {
                        hex_str += d;
                    } else {
                        break;
                    }
                }
                
                if(hex_str.length() > 0) {
                    std::cout << hex_str << ' ' << to_decimal(hex_str) << std::endl;
                }
            }
        }
    }
}
