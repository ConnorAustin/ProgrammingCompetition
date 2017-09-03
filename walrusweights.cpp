#include <cstdio>

bool exists[2001];
bool add_to[2001];

int main() {
    int weights;
    scanf("%d", &weights);
    
    for(int w = 0; w < weights; ++w) {
        int weight;
        scanf("%d\n", &weight);
        
        for(int i = 0; i < 2001; ++i) {
            if(exists[i]) {
                int sum = i + weight;
                if(sum < 2001) {
                    add_to[sum] = true;
                }
            }
        }
        exists[weight] = true;
        
        for(int i = 0; i < 2001; ++i) {
            if(add_to[i]) {
                exists[i] = true;
                add_to[i] = false;
            }
        }
    }

    for(int delta = 0; delta < 1001; ++delta) {
        if(exists[1000 + delta]) {
            printf("%d\n", 1000 + delta);
            return 0;
        }
        
        if(exists[1000 - delta]) {
            printf("%d\n", 1000 - delta);
            return 0;
        }
    }
}