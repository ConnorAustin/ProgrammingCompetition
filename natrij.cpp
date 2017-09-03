#include <cstdio>

int main() {
    int before_hour, before_min, before_sec, after_hour, after_min, after_sec;
    scanf("%d:%d:%d\n%d:%d:%d", &before_hour, &before_min, &before_sec, &after_hour, &after_min, &after_sec);
    
    int diff = after_hour * 3600 - before_hour * 3600 + after_min * 60 - before_min * 60 + after_sec - before_sec;
    if(diff <= 0) {
        diff += 24 * 3600;
    }
    
    printf("%.2d:%.2d:%.2d\n", diff / 3600, (diff % 3600) / 60, diff % 60);
}


