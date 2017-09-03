#include <cstdio>
#include <algorithm>

int coins_len;
int coins[20];

const int max_val = 200000;
int table[max_val][20];

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
        
        // set up first row
        for(int c = 0; c < max_val; ++c) {
            table[c][0] = c;
        }
        
        for(int c = 1; c < coins_len; ++c) {
            int coin = coins[c];
            
            for(int i = 0; i < coin; ++i) {
                table[i][c] = table[i][c - 1];
            }
            table[coin][c] = 1;
            
            for(int val = coin + 1; val < max_val; ++val) {
                table[val][c] = table[val - coin][c] + 1;
                if(table[val][c] > table[val][c - 1]) {
                    printf("%d\n", val);
                    goto done;
                }
            }
        }
        puts("-1");
        done:
        continue;
    }
}
