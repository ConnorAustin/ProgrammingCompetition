#include <cstdio>
#include <algorithm>

int table[100][100];
int cost[100][100];

int width, height;

bool updated;

void update(int x, int y, int c) {
    int alt_cost = table[x][y] + c;
    if(cost[x][y] == -1) {
        cost[x][y] = alt_cost;
        updated = true;
    } else if(cost[x][y] > alt_cost) {
        cost[x][y] = alt_cost;
        updated = true;
    }
}

void minify() {
    cost[0][0] = table[0][0];
    for(int y = 0; y < height; ++y)
    for(int x = 0; x < width; ++x) {
        int c = cost[x][y];
        
        if(x > 0) {
            update(x - 1, y, c);
        }
        if(x < width - 1) {
            update(x + 1, y, c);
        }
        
        if(y > 0) {
            update(x, y - 1, c);
        }
        if(y < height - 1) {
            update(x, y + 1, c);
        }
    }
}

int main() {
    while(true) {
        scanf("%d %d", &height, &width);
        if(height == 0) {
            return 0;
        }
        
        for(int y = 0; y < height; ++y)
        for(int x = 0; x < width;  ++x) {
            cost[x][y] = -1;
            scanf("%d", &table[x][y]);
        }
        
        updated = true;
        while(updated) {
            updated = false;
            minify();
        }
        
        printf("%d\n", cost[width - 1][height - 1]);
    }
}
