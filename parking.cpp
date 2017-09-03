#include <cstdio>
#include <algorithm>

int costs[4];
int s1, e1, s2, e2, s3, e3;

int intersects(int s, int ss, int se) {
    return s > ss && s <= se;
}

int intersections(int s) {
    return intersects(s, s1, e1) + intersects(s, s2, e2) +  intersects(s, s3, e3);
}

int main() {
    scanf("%d %d %d", &costs[1], &costs[2], &costs[3]); 
    scanf("%d %d %d %d %d %d\n", &s1, &e1, &s2, &e2, &s3, &e3);
    
    costs[0] = 0;
    costs[2] *= 2; // dumbest fine-print detail
    costs[3] *= 3; // I've ever encountered
    
    int index = std::min(std::min(s1, s2), s3);
    int end   = std::max(std::max(e1, e2), e3) + 1;
    int amt   = intersections(index);
    int cost  = 0;
    
    int s = index;
    while(s < end) {
        cost += costs[amt];
        amt = intersections(++s);
    }
    printf("%d\n", cost);
}
