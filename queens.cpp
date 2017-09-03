#include <cstdio>
#include <cstdlib>

struct pos {
    int x, y;
};

pos queenPos[5000];

int main() {
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; ++i) {
        scanf("%d %d", &queenPos[i].x, &queenPos[i].y);
    }
    
    for(int i = 0; i < n - 1; ++i) {
        const pos p = queenPos[i];
        
        for(int j = i + 1; j < n; ++j) {
            const pos o = queenPos[j];
            if(p.y == o.y || p.x == o.x || abs(p.x - o.x) - abs(p.y - o.y) == 0) {
                puts("INCORRECT");
                return 0;
            }
        }
    }
    
    puts("CORRECT");
}
