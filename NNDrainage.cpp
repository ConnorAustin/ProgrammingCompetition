#include <cstdio>
#include <cstring>

int  map[50][50];
bool d[50][50];
int  w, h;
int  puddles;
bool updated;

bool update_drain(int from_x, int from_y, int to_x, int to_y) {
    if(to_x == -1 || to_x == w || to_y == -1 || to_y == h) {        
        d[from_x][from_y] = true;
        updated = true;
        return true;
    }
    
    int from_height = map[from_x][from_y];
    int to_height = map[to_x][to_y];
    
    bool can_drain = d[to_x][to_y] & (from_height >= to_height);
    if(can_drain) {
        d[from_x][from_y] = true;
        updated = true;
        return true;
    }
    return false;
}

void plumbify() {
    puddles = 0;    
    for(int y = 0; y < h; ++y)
    for(int x = 0; x < w; ++x) {
        if(!d[x][y]) {
            ++puddles;
            update_drain(x, y, x - 1, y) ||
            update_drain(x, y, x + 1, y) ||
            update_drain(x, y, x, y - 1) ||
            update_drain(x, y, x, y + 1) ||
            update_drain(x, y, x - 1, y - 1) ||
            update_drain(x, y, x + 1, y - 1) ||
            update_drain(x, y, x - 1, y + 1) ||
            update_drain(x, y, x + 1, y + 1);
        }
    }
}

int main() {
    while(true) {
        scanf("%d %d", &h, &w);
        if(h == 0) {
            return 0;
        }
        
        for(int y = 0; y < h; ++y) {
            for(int x = 0; x < w; ++x) {
                char c;
                do {
                    scanf("%c", &c);
                } while(c == ' ' || c == '\n');
                map[x][y] = (int)(c - '0');
            }
        }
        
        memset(d, false, sizeof(d));
        
        updated = true;
        while(updated) {
            updated = false;
            plumbify();
        }
        
        if(puddles == 0) {
            puts("This property has perfect drainage.");
        } else {
            printf("This property has puddles that form in %d square(s).\n", puddles);
        }
    }
}
