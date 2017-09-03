#include <algorithm>
#include <cstdio>

int arr[101];
int len;

bool check() {
    int diff = arr[1] - arr[0];
    for(int i = 2; i < len; ++i) {
        if(arr[i] - arr[i - 1] != diff) {
            return false;
        }
    }
    return true;
}

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        scanf("%d", &len);
        
        for(int i = 0; i < len; ++i) {
            scanf("%d", &arr[i]);
        }
        
        if(check()) {
            puts("arithmetic");
            continue;
        }
        
        std::sort(std::begin(arr), std::begin(arr) + len);
        
        if(check()) {
            puts("permuted arithmetic");
            continue;
        }
        
        puts("non-arithmetic");
    }
}
