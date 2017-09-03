#include <iostream>
#include <cstdint>

#define u64 uint64_t

int main() {
    while(true) {
        u64 n;
        std::cin >> n;
        
        if(n == 0) {
            break;
        }
        
        u64 n3 = n / 3;
        u64 sum = 3 * ((n3 * (n3 + 1)) / 2);
        
        u64 n5 = n / 5;
        sum += 5 * ((n5 * (n5 + 1)) / 2);
        
        u64 n15 = n / 15;
        sum -= 15 * ((n15 * (n15 + 1)) / 2);
        
        std::cout << sum << std::endl;
    }
}
