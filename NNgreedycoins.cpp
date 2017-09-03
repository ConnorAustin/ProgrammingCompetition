/*
Thanks for the broken test case!

I also was able to compress the table down to a 1-dimensional array after noticing
that you don't need a element in the row before after passing it in the algorithm so that's cool
*/

#include <cstdio>
#include <algorithm>

int coins_len;
int coins[20];

const int max_val = 200000;
int table[max_val];

int greedy_val(int val) {
    int coins_needed = 0;
    
    for(int c = coins_len - 1; c >= 0; --c) {
        int coin = coins[c];
        int needed = val / coin;
        val -= coin * needed;
        coins_needed += needed;
    }
    return coins_needed;
}

int main() {
    bool exit = false;
    
    int coin;
    scanf("%d", &coin);
    
    while(!exit) {
        coins_len = 1;
        coins[0] = 1;
        
        while(true) {
            scanf("%d", &coin);
            
            if(coin == 1) {
                break;
            }
            
            else if(coin == 0) {
                exit = true;
                break;
            }
            
            coins[coins_len++] = coin;
        }
        
        for(int c = 0; c < max_val; ++c) {
            table[c] = c;
        }
        
        for(int c = 1; c < coins_len; ++c) {
            int coin = coins[c];
            table[coin] = 1;
            
            for(int val = coin + 1; val < max_val; ++val) {
                table[val] = std::min(table[val - coin] + 1, table[val]);
            }
        }
        
        for(int v = 0; v < max_val; ++v) {
            if(greedy_val(v) > table[v]) {
                printf("%d\n", v);
                goto done;
            }
        }
        puts("-1");
        done:
        continue;
    }
}
