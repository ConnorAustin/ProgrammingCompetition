#include <iostream>

int numbers[12];

bool is_range_island(int start, int end, int smallest) {
    for(; start <= end; ++start) {
        if(numbers[start] <= smallest) {
            return false;
        }
    }
    return true;
}

int main() {
    int cases;
    std::cin >> cases;
    for(int c = 0; c < cases; ++c) {
        int test_case;
        std::cin >> test_case;
        
        for(int i = 0; i < 12; ++i) {
            std::cin >> numbers[i];
        }
        
        int amount = 0;
        for(int start = 1; start < 12; ++start) {
            for(int end = 11; end >= start; --end) {
                if(is_range_island(start, end, std::max(numbers[start - 1], numbers[end + 1]))) {
                    ++amount;
                }
            }
        }
        std::cout << test_case << ' ' << amount << std::endl;
    }
}