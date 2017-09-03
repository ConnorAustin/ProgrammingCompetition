#include <cstdio>
#include <cstdint>
#define u64 uint64_t

int groups[5000];
u64 group_sum[5000];
u64 skips[5000];

int main() {
    int cases;
    scanf("%d\n", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int group_len, rides, seats;
        scanf("%d %d %d", &rides, &seats, &group_len);

        for(int g = 0; g < group_len; ++g) {
            scanf("%d", &groups[g]);
        }
        
        int skip = 0;
        int skips_len = 0;
        int repeat_index = -1;
        
        for(int n = 0; n < group_len + 20; ++n) {
            int reserved = 0;
            
            int g;
            for(g = 0; g < group_len; ++g) {
                if(reserved + groups[(g + skip) % group_len] <= seats) {
                    reserved += groups[(g + skip) % group_len];
                } else {
                    break;
                }
            }
            
            skips[skips_len++] = skip;
            
            if(g != 0) {
                skip = (skip + g) % group_len;
            } else {
                skip = (skip + 1) % group_len;
            }
            
            for(int i = 0; i < skips_len - 1; ++i) {
                if(skip == skips[i]) {
                    repeat_index = i;
                    break;
                }
            }
            
            group_sum[n] = reserved;
            
            if(repeat_index != -1) {
                break;
            }
        }
        
        u64 cost = 0;
        for(int i = 0; i < repeat_index; ++i) {
            cost += group_sum[i];
        }
        
        u64 repeat_total = 0;
        for(int i = repeat_index; i < skips_len; ++i) {
            repeat_total += group_sum[i];
        }
        
        rides -= repeat_index;
        int repeat_times = rides / (skips_len - repeat_index);
        rides %= (skips_len - repeat_index);
        cost += repeat_times * repeat_total;
        
        for(int r = 0; r < rides; ++r) {
            cost += group_sum[repeat_index + r];
        }
        
        printf("Case #%d: %llu\n", c + 1, cost);
    }
}
