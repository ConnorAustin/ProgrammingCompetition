#include <cstdio>
#include <algorithm>

int table[100][100];
int sum[100][100];
int width, height;

void add(int cur_sum, int x, int y) {
    if(x == width || x == -1 || y == height || y == -1) {
        return;
    }
    
    if(sum[x][y] == -1 || sum[x][y] > cur_sum + table[x][y]) {
        int new_sum = cur_sum + table[x][y];
        
        sum[x][y] = new_sum;
        add(new_sum, x + 1, y);
        add(new_sum, x, y + 1);
        add(new_sum, x, y - 1);
    }
}

int main() {
    while(true) {
        scanf("%d %d", &height, &width);
        if(height == 0) {
            return 0;
        }
        
        for(int y = 0; y < height; ++y)
        for(int x = 0; x < width; ++x) {
            sum[x][y] = -1;
            scanf("%d", &table[x][y]);
        }
        
        for(int y = 0; y < height; ++y) {
            add(0, 0, y);
        }
        
        int min_sum = sum[width - 1][0]; 
        for(int y = 1; y < height; ++y) {
            min_sum = std::min(min_sum, sum[width - 1][y]);
        }
        
        printf("%d\n", min_sum);
    }
}
