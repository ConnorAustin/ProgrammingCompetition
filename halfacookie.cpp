#include <cstdio>
#include <cmath>
#include <algorithm>

int main() {
    double radius, x, y;
    while(scanf("%lf %lf %lf", &radius, &x, &y) == 3) {
        double dist = std::sqrt(x * x + y * y);
        if(dist >= radius) {
            puts("miss");
            continue;
        }
        
        double angle = std::acos(dist / radius);
        double sector_area = angle * radius * radius;
        double chord_area = sector_area - 2.0 * (dist * radius * sin(angle) / 2.0);
        double area_left = (M_PI * radius * radius) - chord_area;
        printf("%.6f %.6f\n", std::max(area_left, chord_area), std::min(area_left, chord_area));
    }
}