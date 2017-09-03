#include <iostream>
#include <cmath>
#include <bitset>

std::bitset<100000001> not_prime;

void gen_primes(int up_to) {
    not_prime[0] = true;
    not_prime[1] = true;
    
    for(int n = 2; n < sqrt(up_to); ++n) {
        if(!not_prime[n]) {
            for(int j = n * n; j < up_to; j+=n) {
                not_prime[j] = true;
            }
        }
    }
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    int n, q;
    std::cin >> n >> q;
    
    gen_primes(n + 1);
    
    int primes = 0;
    for(int i = 2; i <= n; ++i) {
        if(!not_prime[i]) {
            ++primes;
        }
    }
    std::cout << primes << std::endl;
    
    for(int i = 0; i < q; ++i) {
        int number;
        std::cin >> number;
        std::cout << !not_prime[number] << std::endl;
    }
}
