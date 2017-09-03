#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <functional>

enum direction {
    fwd,
    bck
};

struct mirror {
    int index;
    int x, y;
    direction dir;
    mirror* left;
    mirror* up;
    mirror* right;
    mirror* down;
};

struct Result {
    int crosses, x, y;
};

struct line {
    int x1, y1, x2, y2;
    line() { }
    line(int x, int y, int a, int b) : x1(x), y1(y), x2(a), y2(b) { }
};

int height, width;
int mirrors_len;

mirror mirrors[200000 + 200000];
mirror mirrors_sort[200000 + 200000];

std::vector<line> horiz_lasers;
std::vector<line> vert_lasers;

Result result;

void read_in() {
    result.x = 2000001;
    result.y = 2000001;
    result.crosses = 0;
    
    mirrors_len = 0;
    
    horiz_lasers.clear();
    horiz_lasers.reserve(500000);
    
    vert_lasers.clear();
    vert_lasers.reserve(500000);
    
    int fwd_m;
    int bck_m;
    if(scanf("%d %d %d %d", &height, &width, &fwd_m, &bck_m) != 4) {
        exit(0);
    }
    
    auto add_mirror = [](int x, int y, direction dir) {
        mirrors[mirrors_len].index = mirrors_len;
        
        mirrors[mirrors_len].x = x - 1;
        mirrors[mirrors_len].y = y - 1;
        mirrors[mirrors_len].dir = fwd;
        
        mirrors[mirrors_len].up = nullptr;
        mirrors[mirrors_len].left = nullptr;
        mirrors[mirrors_len].right = nullptr;
        mirrors[mirrors_len].down = nullptr;
        
        mirrors_sort[mirrors_len] = mirrors[mirrors_len];
        ++mirrors_len;
    };
    
    int x, y;
    
    for(int i = 0; i < fwd_m; ++i) {
        scanf("%d %d", &y, &x);
        add_mirror(x, y, fwd);
    }
    
    for(int i = 0; i < bck_m; ++i) {
        scanf("%d %d", &y, &x);
        add_mirror(x, y, bck);
    }
}

std::pair<mirror*, mirror*> connect_mirrors() {
    mirror* start = nullptr;
    mirror* end = nullptr;
    
    // sort by x and y but prefer x
    std::sort(std::begin(mirrors_sort), std::begin(mirrors_sort) + mirrors_len, [](const mirror& m, const mirror& o) {
        return m.x == o.x ? m.y < o.y : m.x < o.x;
    });
    
    for(int i = 1; i < mirrors_len; ++i) {
        if(mirrors_sort[i].x == mirrors_sort[i - 1].x) {
            auto& m = mirrors_sort[i];
            auto& o = mirrors_sort[i - 1];
            
            mirrors[m.index].up = &mirrors[o.index];
            mirrors[o.index].down = &mirrors[m.index];
        }
    }
    
    // sort by y and x but prefer y
    std::sort(std::begin(mirrors_sort), std::begin(mirrors_sort) + mirrors_len, [](const mirror& m, const mirror& o) {
        return m.y == o.y ? m.x < o.x : m.y < o.y;
    });
    
    for(int i = 1; i < mirrors_len; ++i) {
        if(mirrors_sort[i].y == mirrors_sort[i - 1].y) {
            auto& m = mirrors_sort[i];
            auto& o = mirrors_sort[i - 1];
            
            mirrors[m.index].left = &mirrors[o.index];
            mirrors[o.index].right = &mirrors[m.index];
        }
    }
    
    // Find the starting and ending mirrors
    if(mirrors_len > 0) {
        if(mirrors_sort[0].y == 0) {
            start = &mirrors[mirrors_sort[0].index];
        }
        
        if(mirrors_sort[mirrors_len - 1].y == height - 1) {
            end = &mirrors[mirrors_sort[mirrors_len - 1].index];
        }
    }
    return std::make_pair(start, end);
}

// Returns true if we make it to the bottom right
bool trace(bool right, mirror* start, const std::function<void(int, int, int, int)>& callback) {
    bool left = !right;
    bool up = false;
    bool down = false;
    
    if(start == nullptr) {
        if(right) {
            callback(-1, 0, width, 0);
        } else {
            callback(-1, height - 1, width, height - 1);
        }
        return false;
    }
    
    if(right) {
        callback(-1, 0, start->x, 0);
    } else {
        callback(start->x, height - 1, width, height - 1);
    }
    
    mirror* cur = start;
    
    int x = start->x;
    int y = start->y;
    
    while(true) {
        switch(cur->dir) {
            case fwd:
                std::swap(left, down);
                std::swap(right, up);
                break;
            case bck:
                std::swap(right, down);
                std::swap(left, up);
                break;
        }
        
        mirror* next = nullptr;
        
        if(right) {
            next = cur->right;
            if(next == nullptr) {
                callback(x, y, width, y);
                
                if(y == height - 1) {
                    return true; // We made it to the bottom right, return true
                }
                return false;
            }
            callback(x, y, next->x, y);
        }
        else if(left) {
            next = cur->left;
            if(next == nullptr) {
                callback(-1, y, x, y);
                return false;
            }
            callback(next->x, y, x, y);
        }
        else if(down) {
            next = cur->down;
            if(next == nullptr) {
                callback(x, y, x, height);
                return false;
            }
            callback(x, y, x, next->y);
        }
        else if(up) {
            next = cur->up;
            if(next == nullptr) {
                callback(x, -1, x, y);
                return false;
            }
            callback(x, next->y, x, y);
        }
        cur = next;
        x = cur->x;
        y = cur->y;
    }
}

void add_laser(int x1, int y1, int x2, int y2) {
    if(x1 == x2) {
        vert_lasers.emplace_back(x1, y1, x2, y2);
    } else {
        horiz_lasers.emplace_back(x1, y1, x2, y2);
    }
}

void intersect(int x1, int y1, int x2, int y2) {
    auto found_cross = [](int x, int y) {
        ++result.crosses;
        if(y < result.y || (y == result.y && x < result.x)) {
            result.x = x;
            result.y = y;
        }
    };
    
    // Vertical line, check horizontal lasers
    if(x1 == x2) {
        const int x = x1;
        
        for(const auto& l : horiz_lasers) {
            const int y = l.y1;
            
            if(x > l.x1 && x < l.x2 && y > y1 && y < y2) {
                found_cross(x, y);
            }
        }
    }
    // Horizontal line, check vertical lasers 
    else {
        const int y = y1;
        
        for(const auto& l : vert_lasers) {
            const int x = l.x1;
            
            if(y > l.y1 && y < l.y2 && x > x1 && x < x2) {
                found_cross(x, y);
            }
        }
    }
} 

int main() {
    for(int c = 1;; ++c) {
        read_in();
        
        auto start_end_pair = connect_mirrors();
        mirror* start = start_end_pair.first;
        mirror* end = start_end_pair.second;
        
        // Trace the laser from the start
        if(trace(true, start, add_laser)) {
            // We got to the bottom right. This must already be solvable
            printf("Case %d: 0\n", c);
            continue;
        }
        
        // Trace a laser from the detector
        trace(false, end, intersect);
        
        if(result.crosses == 0) {
            // The lasers never crossed so this is impossible
            printf("Case %d: impossible\n", c);
            continue;
        }
        printf("Case %d: %d %d %d\n", c, result.crosses, result.y + 1, result.x + 1);
    }
}

// #include <cstdio>
// #include <cstdlib>
// #include <algorithm>
// #include <cstdint>
// 
// enum direction {
//     fwd,
//     bck,
//     none
// };
// 
// struct A {
//     int crosses, x, y;
// };
// 
// struct grid {
//     int mirror;
//     int crossed;
// };
// 
// int height, width;
// int* mirrors[1000000];
// int* crossed[1000000];
// 
// template<typename T>
// int& get(T* t, int x, int y) {
//     return (t[x])[y];
// }
// 
// void read_in() {
//     int fwd_m;
//     int bck_m;
//     if(scanf("%d %d %d %d", &height, &width, &fwd_m, &bck_m) != 4) {
//         exit(0);
//     }
//     
//     for(int x = 0; x < width; ++x) {
//         for(int y = 0; y < height; ++y) {
//             get(mirrors, x, y) = none;
//             get(crossed, x, y) = false;
//         }
//     }
//     
//     for(int i = 0; i < fwd_m; ++i) {
//         int x, y;
//         scanf("%d %d", &y, &x);
//         get(mirrors, x - 1, y - 1) = fwd;
//     }
//     
//     for(int i = 0; i < bck_m; ++i) {
//         int x, y;
//         scanf("%d %d", &y, &x);
//         get(mirrors, x - 1, y - 1) = bck;
//     }
// }
// 
// bool fire_laser() {
//     int x = 0;
//     int y = 0;
//     int right = 1;
//     int left = 0;
//     int up = 0;
//     int down = 0;
//     
//     while(true) {
//         get(crossed, x, y) = true;
//         x += right;
//         x -= left;
//         y += down;
//         y -= up;
//         
//         if(y < 0 || y == height || x < 0 || x == width) {
//             if(x == width && y == height - 1) {
//                 return true;
//             }
//             return false;
//         }
//         
//         switch(get(mirrors, x, y)) {
//             case fwd:
//                 std::swap(left, down);
//                 std::swap(right, up);
//                 break;
//             case bck:
//                 std::swap(left, up);
//                 std::swap(right, down);
//                 break;
//             case none:
//                 break;
//         }
//     }
// }
// 
// A fire_detector_laser() {
//     A result;
//     result.crosses = 0;
//     result.x = 1000000;
//     result.y = 1000000;
//     
//     int x = width - 1;
//     int y = height - 1;
//     int right = 0;
//     int left = 1;
//     int up = 0;
//     int down = 0;
//     
//     while(true) {
//         if(get(crossed, x, y)) {
//             ++result.crosses;
//             if(y < result.y || (y == result.y && x < result.x)) {
//                 result.x = x;
//                 result.y = y;
//             }
//         }
//         
//         x += right;
//         x -= left;
//         y += down;
//         y -= up;
//         
//         if(y < 0 || y == height || x < 0 || x > width) {
//             return result;
//         }
//         
//         switch(get(mirrors, x, y)) {
//             case fwd:
//                 std::swap(left, down);
//                 std::swap(right, up);
//                 break;
//             case bck:
//                 std::swap(right, down);
//                 std::swap(left, up);
//                 break;
//             case none:
//                 break;
//         }
//     }
// }
// 
// int main() {
//     for(int i = 0; i < 1000000; ++i) {
//         crossed[i] = new int[1000000];
//         mirrors[i] = new int[1000000];
//     }
//     
//     for(int c = 1;; ++c) {
//         read_in();
//         
//         if(fire_laser()) {
//             printf("Case %d: 0\n", c);
//             continue;
//         }
//         A r = fire_detector_laser();
//         if(r.crosses == 0) {
//             printf("Case %d: impossible\n", c);
//             continue;
//         }
//         printf("Case %d: %d %d %d\n", c, r.crosses, r.y + 1, r.x + 1);
//     }
// }
// 
