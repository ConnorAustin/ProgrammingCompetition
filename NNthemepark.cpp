#include <cstdio>

int groups[1000];

int main() {
    int cases;
    scanf("%d\n", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int group_len, rides, seats;
        scanf("%d %d %d", &rides, &seats, &group_len);

        for(int g = 0; g < group_len; ++g) {
            scanf("%d", &groups[g]);
        }
        
        int cost = 0;
        int skip = 0;
        
        for(int r = 0; r < rides; ++r) {
            int reserved = 0;
            
            int g;
            for(g = 0; g < group_len; ++g) {
                if(reserved + groups[(g + skip) % group_len] <= seats) {
                    reserved += groups[(g + skip) % group_len];
                } else {
                    break;
                }
            }
            
            if(g != 0) {
                skip += g;
            } else {
                ++skip;
            }
            
            cost += reserved;
        }
        
        printf("Case #%d: %d\n", c + 1, cost);
    }
}
