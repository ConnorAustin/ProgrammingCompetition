#include <iostream>
#include <vector>

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;
    size_t f = str.find(':');
    result.push_back(str.substr(0, f));
    result.push_back(str.substr(f + 1, -1));
    return result;
}

int sum() {
    
}

int main() {
    int limit;
    std::cin >> limit;
    
    
}