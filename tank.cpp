#include <cstdio>
#include <algorithm>

struct vertex {
    int x, y;
};

struct trapezoid {
    vertex ll, lr, ul, ur;
};

int poly_len;
vertex poly[100];
vertex sorted_poly[100];

int traps_len = 0;
trapezoid traps[500];

int trap_area(const trapezoid& trap) {
    return (((trap.lr.x - trap.ll.x) + (trap.ur.x - trap.ul.x)) * (trap.ur.y - trap.lr.y)) / 2;
}

// returns the x position along the line formed by two vertices when given a y along that line
int get_x_from_y(const vertex& p1, const vertex& p2, int y) {
    // Ax + By = C
    // x = (C - By) / A
    const int A = p2.y - p1.y;
    const int B = p1.x - p2.x;
    const int C = A * p1.x + B * p1.y;
    
    return (C - B * y) / A;
}

vertex get_partner(const vertex& v) {
    for(int p = 0; p < poly_len; ++p) {
        const vertex& other = poly[p];
        if(other.y == v.y && other.x != v.x) {
            return other;
        }
    }
    
    for(int p = 0; p < poly_len - 1; ++p) {
        vertex upper = poly[p];
        vertex lower = poly[p + 1];
        
        if(upper.y < lower.y) {
            std::swap(upper, lower);
        }
        
        if(v.y > lower.y && v.y < upper.y) {
            int x = get_x_from_y(lower, upper, v.y);
            return {x, v.y};
        }
    }
    
    vertex upper = poly[0];
    vertex lower = poly[poly_len - 1];
    
    if(upper.y < lower.y) {
        std::swap(upper, lower);
    }
    
    if(v.y > lower.y && v.y < upper.y) {
        int x = get_x_from_y(lower, upper, (int)v.y);
        return {x, v.y};
    }
    
    return v;
}

void polygonArea() { 
    int area = 0;         // Accumulates area in the loop
    int j = poly_len - 1;  // The last vertex is the 'previous' one to the first

    for (int i=0; i < poly_len; i++) { 
        area += (poly[j].x + poly[i].x) * (poly[j].y - poly[i].y); 
        j = i;  //j is previous vertex to i
    }
    printf("real-area: %d\n", -area / 2);
}

void trapezoidize() {
    int area = 0;
    vertex ll = sorted_poly[0];
    vertex lr = sorted_poly[1];
    
    trapezoid trap;
    
    if(ll.x > lr.x) {
        std::swap(ll, lr);
    }
    
    for(int i = 2; i < poly_len - 1; ++i) {
        vertex ul = sorted_poly[i];
        vertex ur = get_partner(ul);
        
        if(ur.x < ul.x) {
            std::swap(ul, ur);
        }
        trap.ul = ul;
        trap.ur = ur;
        trap.ll = ll;
        trap.lr = lr;
        
        ll = ul;
        lr = ur;
        traps[traps_len++] = trap;
        area += trap_area(trap);
    }
    
    polygonArea();
    printf("total trap area: %d\n", area);
}

int main() {
    int depth, liters;
    scanf("%d %d %d", &poly_len, &depth, &liters);
    liters *= 1000;
    
    for(int i = 0; i < poly_len; ++i) {
        scanf("%d %d", &poly[i].x, &poly[i].y);
        sorted_poly[i] = poly[i];
    }
    
    std::sort(std::begin(sorted_poly), std::begin(sorted_poly) + poly_len, [](const vertex& v1, const vertex& v2) {
        return v1.y < v2.y;
    });
    
    trapezoidize();
        
    /*
    for(int i = 0; i < traps_len; ++i) {
        int volume = trap_area(traps[i]) * depth;
        if(volume < liters) {
            liters -= volume;
        } else if(volume == liters) {
            printf("%d\n", traps[i].ur.y);
            return 0;
        } else {
            // liters == depth * area == (((lr.x - ll.x) + (xr - xl)) * (y - lr.y)) / 2;    
            
            // A = ll.y - y
            // B = x1 - ll.x
            // C = (ll.y - y) * x1 + (x1 - ll.x) * y
            // xl = ((ll.y - y) * ul.x + (ul.x - ll.x) * y - (ul.x - ll.x) * y) / (ll.y - y)
            // xr = ((lr.y - y) * ur.x + (ur.x - lr.x) * y - (ur.x - lr.x) * y) / (lr.y - y)
            
            // area == depth * (((lr.x - ll.x) + (((lr.y - y) * ur.x + (ur.x - lr.x) * y - (ur.x - lr.x) * y) / (lr.y - y) - ((ll.y - y) * ul.x + (ul.x - ll.x) * y - (ul.x - ll.x) * y) / (ll.y - y))) * (y - lr.y)) / 2
            
            // lr.x == a
            // ll.x == b
            // ll.y == lr.y == c
            // ur.x == d
            // ul.x == e
            // liters == z
            // t == depth
            // t * (((a - b) + (((c - y) * d + (d - a) * y - (d - a) * y) / (c - y) - ((c - y) * e + (e - b) * y - (e - b) * y) / (c - y))) * (y - c)) / 2
            //
            // y = (t * (ac - bc + cd - ce) + 2 * z) / (t * (a - b + d - e))
            const vertex& ll = traps[i].ll;
            const vertex& lr = traps[i].lr;
            const vertex& ul = traps[i].ul;
            const vertex& ur = traps[i].ur;
            
            double y = (double)(depth * (lr.x * ll.y - ll.x * ll.y + ll.y * ur.x - ll.y * ul.x) + 2 * liters) / (depth * (lr.x - ll.x + ur.x - ul.x));
            printf("%.2f\n", y);
            return 0;
        }
    }*/
}
