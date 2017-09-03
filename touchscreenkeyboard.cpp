#include <iostream>
#include <algorithm>

struct pos {
    int x, y;
};

/*
qwertyuiop
asdfghjkl
zxcvbnm
*/

pos keyboard[] = { 
    {0, 1}, // a
    {4, 2}, // b
    {2, 2}, // c
    {2, 1}, // d
    {2, 0}, // e
    {3, 1}, // f
    {4, 1}, // g
    {5, 1}, // h
    {7, 0}, // i
    {6, 1}, // j
    {7, 1}, // k
    {8, 1}, // l
    {6, 2}, // m
    {5, 2}, // n
    {8, 0}, // o
    {9, 0}, // p
    {0, 0}, // q
    {3, 0}, // r
    {1, 1}, // s
    {4, 0}, // t
    {6, 0}, // u
    {3, 2}, // v
    {1, 0}, // w
    {1, 2}, // x
    {5, 0}, // y
    {0, 2}, // z
};

struct suggestion {
    std::string str;
    int dist;
};

int suggestions_len;
suggestion suggestions[10];

int dist(const std::string& t, const std::string& s) {
    int result = 0;
    for(int c = 0; c < t.length(); ++c) {
        const pos& p1 = keyboard[t[c] - 'a'];
        const pos& p2 = keyboard[s[c] - 'a'];
        result += std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
    }
    return result;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    int cases;
    std::cin >> cases;
    
    for(int c = 0; c < cases; ++c) {
        std::string typed;
        std::cin >> typed >> suggestions_len;
        
        for(int s = 0; s < suggestions_len; ++s) {
            std::cin >> suggestions[s].str;
            suggestions[s].dist = dist(typed, suggestions[s].str);
        }
        
        std::sort(std::begin(suggestions), std::begin(suggestions) + suggestions_len, [](const suggestion& s1, const suggestion& s2) {
            if(s1.dist == s2.dist) {
                return s1.str < s2.str;
            }
            return s1.dist < s2.dist;
        });
        
        for(int s = 0; s < suggestions_len; ++s) {
            std::cout << suggestions[s].str << ' ' << suggestions[s].dist << std::endl;
        }
    }
}
