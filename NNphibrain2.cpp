#include <cstdio>
#include <cmath>

double n_over_phi[250000];

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
}

void gen_n_over_phi() {
    n_over_phi[0] = -1.0;
    n_over_phi[1] = -1.0;
    
    for(int i = 2; i <= 250000; ++i) {
        if(!not_prime[i]) {
            primes[++primes_len] = i;
            n_over_phi[i] = (double)i / (double)(i - 1);
            continue;
        }
        
        double ans = i;
        
        for(int p = 0; p < primes_len && primes[p] <= i; ++p) {
            if(i % primes[p] == 0) {
                ans *= (1.0 - 1.0/(double)(primes[p]));
            }
        }
        n_over_phi[i] = (double)i / ans;
    }
}

int main() {
    gen_primes();
    gen_n_over_phi();
    
    while(true) {
        int a, b;
        int read = scanf("%d %d", &a, &b);
        if(read != 2) {
            return 0;
        }
        
        double max_val = -1;
        int max_n = -1;
        
        for(; a <= b; ++a) {
            if(n_over_phi[a] > max_val) {
                max_val = n_over_phi[a];
                max_n = a;
            }
        }
        printf("%d\n", max_n);
    }
}
