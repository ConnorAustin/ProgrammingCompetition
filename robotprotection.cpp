#include <cstdio>
#include <cmath>
#include <vector>

struct v2 {
    int x, y;
};

int points_len;
v2 points[10000];

int find_lowest_point() {
    int p_index = 0;
    int minY = points[0].y;
    int maxX = points[0].x;
    
    // Prioritize minY
    for(int p = 0; p < points_len; ++p) {
        if(minY > points[p].y || (minY == points[p].y && maxX < points[p].x)) {
            p_index = p;
            minY = points[p].y;
            maxX = points[p].x;
        }
    }
    return p_index;
}

double area(const std::vector<int>& poly) {
    double result = 0;
    
    int prev_index = poly.size() - 1;
    for(int i = 0; i < poly.size(); ++i) {
        const v2& a = points[poly[prev_index]];
        const v2& b = points[poly[i]];
        
        result += (a.x + b.x) * (a.y - b.y);
        prev_index = i;
    }
    return result / 2.0;
}

int dot(const v2& a, const v2& b) {
    return a.x * b.x + a.y * b.y;
}

v2 minus(const v2& a, const v2& b) {
    return v2{a.x - b.x, a.y - b.y};
}

double mag(const v2& v) {
    return sqrtf(v.x * v.x + v.y * v.y);
}

double get_angle(const v2& a, const v2& b) {
    return acos(dot(a, b) / (mag(a) * mag(b)));
}

std::vector<int> graham_scan() {
    std::vector<int> poly;
    
    int lp_index = find_lowest_point();
    poly.push_back(lp_index);
    
    double min_ang = 9999999;
    int min_index = 0;
    
    double max_ang = -1;
    int max_index = 0;
    
    v2 right{1, 0};
    for(int p = 0; p < points_len; ++p) {
        if(p == lp_index) {
            continue;
        }
        
        double ang = get_angle(right, minus(points[p], points[lp_index]));
        if(ang < min_ang) {
            min_ang = ang;
            min_index = p;
        }
        if(ang > max_ang) {
            max_ang = ang;
            max_index = p;
        }
    }
    poly.push_back(max_index);
    
    int prev_index = lp_index;
    int cur_index = max_index;
    
    int best_index = -1;
    while(best_index != min_index) {
       max_ang = -1;
       for(int p = 0; p < points_len; ++p) {
           if(p == cur_index) {
               continue;
           }
           
           double ang = get_angle(minus(points[prev_index], points[cur_index]), minus(points[p], points[cur_index]));
           if(ang > max_ang) {
               max_ang = ang;
               best_index = p;
           }
       }
       
       poly.push_back(best_index);
       prev_index = cur_index;
       cur_index = best_index;
    }
    return poly;
}

int main() {
    while(true) {
        scanf("%d", &points_len);
        if(points_len == 0) {
            break;
        }
        
        for(int p = 0; p < points_len; ++p) {
            scanf("%d %d", &points[p].x, &points[p].y);
        }
        
        
        printf("%f\n", area(graham_scan()));
    }
}