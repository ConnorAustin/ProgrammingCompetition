#include <cstdio>
#include <algorithm>

int stores[20];

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int stores_len;
        scanf("%d", &stores_len);
        
        for(int s = 0; s < stores_len; ++s) {
            scanf("%d", &stores[s]);
        }
        std::sort(std::begin(stores), std::begin(stores) + stores_len);
        
        int result = 0;
        for(int s = 1; s < stores_len; ++s) {
            result += stores[s] - stores[s - 1];
        }
        printf("%d\n", result * 2);
    }
}
