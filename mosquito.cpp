#include <cstdio>

int main() {
    while(true) {
        int m, p, l, e, r, s, n;
        if(scanf("%d %d %d %d %d %d %d\n", &m, &p, &l, &e, &r, &s, &n) != 7) {
            return 0;
        }
        
        int eggs = 0;
        int nm, np;
        
        for(int i = 0; i < n; ++i) {
            np = l / r;
            nm = p / s;
            eggs = m * e;
            
            l = eggs;
            p = np;
            m = nm;
        }
        printf("%d\n", m);
    }
}
