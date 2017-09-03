#include <cstdio>
#include <algorithm>

int gz[100000];
int mgz[100000];

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int gz_len, mgz_len;
        scanf("%d %d", &gz_len, &mgz_len);
        
        for(int g = 0; g < gz_len; ++g) {
            scanf("%d", &gz[g]);
        }
        
        for(int g = 0; g < mgz_len; ++g) {
            scanf("%d", &mgz[g]);
        }
        
        std::sort(std::begin(gz), std::begin(gz) + gz_len);
        std::sort(std::begin(mgz), std::begin(mgz) + mgz_len);
        
        int gz_index = 0;
        int mgz_index = 0;
        
        while(true) {
            if(mgz[mgz_index] > gz[gz_index]) {
                if(++gz_index == gz_len) {
                    puts("MechaGodzilla");
                    break;
                }
            } else if(++mgz_index == mgz_len) {
                puts("Godzilla");
                break;
            }
        }
    }
}
