#include <cstdio>

int a, b, c, d, p, m, g;

void check(int t) {
    int attacks = 0;
    if((t - 1) % (a + b) < a) {
        ++attacks;
    }
    
    if((t - 1) % (c + d) < c) {
        ++attacks;
    }
    
    switch(attacks) {
        case 0: puts("none"); break;
        case 1: puts("one"); break;
        case 2: puts("both"); break;
    }
}

int main() {
    scanf("%d %d %d %d %d %d %d", &a, &b, &c, &d, &p, &m, &g);
    check(p);
    check(m);
    check(g);
}