#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

bool slices[1296001];
const int slices_len = sizeof(slices) / sizeof(bool);

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        if(c != 0) {
            memset(slices, 0, sizeof(slices));
        }
        
        double r;
        int theta, minute, second;
        int n;
        
        scanf("%lf %d %d %d %d", &r, &n, &theta, &minute, &second);
        
        while(theta >= 360.0) {
            theta -= 360.0;
        }
        
        second += minute * 60 + theta * 360;
        
        int cur_theta = 0;
        int cur_minute = 0;
        int cur_second = 0;
        
        for(int i = 0; i < n; ++i) {
            bool& s = slices[cur_theta * 60 * 60 + cur_minute * 60 + cur_second];
            
            if(s) {
                break;
            }
            
            s = true;
            
            cur_theta += theta;
            cur_minute += minute;
            cur_second += second;
            
            if(cur_second > 59) {
                cur_second -= 60;
                ++cur_minute;
            }
            if(cur_minute > 59) {
                cur_minute -= 60;
                ++cur_theta;
            }
            if(cur_theta > 359) {
                cur_theta -= 360;
            }
        }
        
        int max_range = 0;
        
        int i = 0;
        while(!slices[i]) {
            ++i;
        }
        
        int j = i + 1;
        while(j < slices_len) {
            if(slices[j]) {
                max_range = std::max(max_range, j - i);
                i = j;
            }
            ++j;
        }
        max_range = std::max(max_range, 1296000 - i);
        
        const double max_angle = (double)max_range / (360.0 * 60.0 * 60.0);
        printf("%f\n", M_PI * r * r * max_angle);
    }
}
