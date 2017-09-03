#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdint>

using u64 = uint64_t;

int main() {
    u64 n, t, a, b, c, t0;
    scanf("%llu %llu %llu %llu %llu %llu", &n, &t, &a, &b, &c, &t0);
    
    std::vector<u64> times;
    times.push_back(t0);
    for(int nn = 0; nn < n - 1; ++nn) {
        times.push_back(((a * times[times.size() - 1] + b) % c) + 1);
    }
    
    std::sort(std::begin(times), std::end(times));
    
    u64 penalty = 0;
    u64 solved = 0;
    u64 cur_time = t;
    
    for(u64 tim : times) {
        if(cur_time < tim) {
            break;
        }
        
        cur_time -= tim;
        ++solved;
        
        penalty += t - cur_time;
        penalty %= 1000000007;
    }
    printf("%llu %llu\n", solved, penalty);
}
