#include <cstdio>
#include <cmath>

int main() {
    unsigned long long area;
    scanf("%llu", &area);
    
    printf("%.10f\n", sqrt((double)area) * 4);
}
