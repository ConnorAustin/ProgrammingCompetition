/*
For brevity, S stands for Single precision IEEE
         and G stands for Gould floating point
*/
#include <cstdio>
#include <iostream>
#include <string>
#include <cstdint>
#include <iomanip>

using uint = uint32_t;

// returns POSITIVE infinity
uint S_INF() {
    uint inf = 0;
    inf |= 255 << 23;
    return inf;
}

// returns POSITIVE zero
uint S_ZERO() {
    return 0;
}

float to_float(uint s) {
    float f;
    float* f_ptr = &f;
    uint* i_ptr = reinterpret_cast<uint*>(f_ptr);
    *i_ptr = s;
    return f;
}

int main() {
    uint x = 127 << 23;
    for(int i = 0; i < 25; ++i) {
        x += 1;
        float f = to_float(x);
        printf("f = %.40f\n", f);
    }
    
    int cases;
    std::cin >> cases;
    for(int c = 0; c < cases; ++c) {
        int test_case;
        std::cin >> test_case;
        
        std::string gould_hex;
        std::cin >> gould_hex;
        
        uint g = (uint)(stol(gould_hex, nullptr, 16));
        uint g_exp = (g >> 24) & 0x7F;
        
        printf("exp: %u\n", g_exp);
        
        uint s = 0;
        s |= g & 0x80000000;
        
        s |= ((g & 0xFFFFFF) >> 1) - 1;
        printf("%d %0.8X\n", test_case, s);
    }
}