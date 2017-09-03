#include <iostream>

int a, b, c, maxI, minI, k;

// k ?= ii*a + B + 1 where B is a sum of b - 1's b - 2's of any amount
// k - ii*a - 1 ?= B

bool check_possible() {
    for(int ii = minI; ii <= maxI; ++ii) {
        int B = k - a * ii - 1;
        if(B == 0) {
            std::cout << "possible" << std::endl;
            return true;
        }
        
        int times = 0;
        for(int bb = b - 1; bb > 0; --bb) {
            times += B / bb;
            B = B % bb;
            
            if(B == 0) {
                if(times <= ii) {
                    std::cout << "possible" << std::endl;
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

int ceil_div(int dividend, int divisor) {
    return (dividend + divisor - 1) / divisor;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    while(true) {
        std::cin >> a >> b >> c >> maxI >> k;
        if(std::cin.eof()) {
            break;
        }
        
        minI = ceil_div(maxI, c);
        if(minI * a + 1 > k || maxI * (a + b) + 1 < k) {
            std::cout << "impossible" << std::endl;
        } else if(!check_possible()) {
            std::cout << "impossible" << std::endl;
        }
    }
}
