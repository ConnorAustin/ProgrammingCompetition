#include <cstdio>

int main() {
    int cases;
    scanf("%d", &cases);
    for(int c = 0; c < cases; ++c) {
        int n, k;
        scanf("%d %d", &n, &k);
        if((k & ((1 << n) - 1)) == (1 << n) - 1) {
            printf("Case #%d: %s\n", c + 1, "ON");
        } else {
            printf("Case #%d: %s\n", c + 1, "OFF");
        }
    }
}