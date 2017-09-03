#include <cstdio>
#include <algorithm>
#define ll long long 

ll matrix[100][100];
ll sum[100][100];

int main() {
    int w, h;
    while(true) {
        scanf("%d %d\n", &h, &w);
        if(w == 0 && h == 0) {
            return 0;
        }
        
        for(int y = 0; y < h; ++y)
        for(int x = 0; x < w; ++x) {
            scanf("%lld", &matrix[x][y]);
        }
        
        for(int y = 0; y < h; ++y) 
        for(int x = 0; x < w; ++x) {
            if(x == 0 && y == 0) {
                sum[0][0] = matrix[0][0];
                continue;
            }
            if(x == 0) {
                sum[x][y] = sum[0][y - 1];
            } else if(y == 0) {
                sum[x][y] = sum[x - 1][0];
            } else {
                sum[x][y] = std::min(sum[x - 1][y], sum[x][y - 1]);
            }
            sum[x][y] += matrix[x][y];
        }
        printf("%lld\n", sum[w - 1][h - 1]);
    }
}
