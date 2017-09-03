#include <fstream>
#include <cmath>

bool not_prime[250001];
int primes[250001];
int primes_len = 0;

void gen_primes() {
    for(int n = 2; n < sqrt(250001); ++n) {
        if(!not_prime[n]) {
            for(int j = n * n; j < 250001; j+=n) {
                not_prime[j] = true;
            }
        }
    }
    
    std::fstream file("primes.txt");
    file << "std::string primes_str=\"00";
    for(int n = 2; n < 250001; ++n) {
        if(!not_prime[n]) {
            file << '1';
        } else {
            file << '0';
        }
    }
    file << "\";";
    file.close();
}

int main() {
    gen_primes();
}
