#include <cstdio>
#include <cmath>

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int movements;
        scanf("%d", &movements);
        
        double x = 0;
        double y = 0;
        double cur_ang = 0;
        
        for(int m = 0; m < movements; ++m) {
            double angle, dist;
            scanf("%lf %lf", &angle, &dist);
            
            cur_ang += angle;
            x -= sin(cur_ang * M_PI / 180.0) * dist;
            y += cos(cur_ang * M_PI / 180.0) * dist;
        }
        printf("%f %f\n", x, y);
    }
}
