#include <cstdio>
#include <algorithm>

int arrives[300000];
int leaves[300000];

int main() {
    int r_len, activity;
    scanf("%d %d", &r_len, &activity);
    
    for(int r = 0; r < r_len; ++r) {
        int arrive;
        scanf("%d", &arrive);
        
        arrives[r] = arrive;
        
        int stays;
        scanf("%d", &stays);
        leaves[r] = arrive + stays + activity;
    }
    
    std::sort(std::begin(arrives), std::begin(arrives) + r_len);
    std::sort(std::begin(leaves), std::begin(leaves) + r_len);
    
    int result = 0;
    int l_len = r_len;
    for(int r = 0; r < r_len; ++r) {
        int ar = arrives[r];
        
        auto it = std::lower_bound(std::begin(leaves), std::begin(leaves) + l_len, ar);
        
        if(*it >= ar && *it - activity <= ar) {
            ++result;
            
            int index = std::distance(std::begin(leaves), it);
            
            for(int i = index; i < l_len; ++i) { 
                std::swap(leaves[i], leaves[i + 1]);
            }
            --l_len;
        }
    }
    printf("%d\n", result);
}