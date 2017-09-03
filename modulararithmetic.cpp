#include <cstdio>
#include <cstdint>
#include <algorithm>

using i64 = int64_t;

i64 inverse(i64 a, i64 mod) {
    i64 i = 0;
    i64 prev_i = 1;
    
    i64 r = mod;
    i64 prev_r = a;
    
    while(r != 0) {
        i64 quotient = prev_r / r;
        
        i64 tmp = prev_r - quotient * r;
        prev_r = r;
        r = tmp;
        
        tmp = prev_i - quotient * i;
        prev_i = i;
        i = tmp;
    }
    
    if(prev_r > 1) {
        return -1;
    }
    
    if(prev_i < 0) {
        return mod + prev_i;
    }
    return prev_i;
}

int main() {
    int mod, cases;
    while(true) {
        scanf("%d %d", &mod, &cases);
        if(mod == 0) {
            return 0;
        }
        
        for(int i = 0; i < cases; ++i) {
            char op;
            i64 lval, rval, ans;
            scanf("%lli %c %lli", &lval, &op, &rval);
            
            switch (op) {
                case '*': 
                    ans = (lval * rval) % mod; 
                    break;
                case '+': 
                    ans = (lval + rval) % mod;
                    break;
                case '-':
                    ans = (mod + lval - rval) % mod;
                    break;
                default: // division case
                    i64 inv = inverse(rval, mod);
                    if(inv == -1) {
                        ans = -1;
                    }
                    else {
                        ans = (lval * inv) % mod;
                    }
                    break;
            }
            printf("%lli\n", ans);
        }
    }
}
