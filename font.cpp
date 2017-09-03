#include <iostream>
#include <cstdint>

using uint = uint32_t;

int words_len = 0;
uint words[25];

uint or_mask(uint mask) {
    uint words_mask = 0;
    for(uint i = 0; i < words_len; ++i) {
        if((mask & (1 << i)) != 0) {
            words_mask |= words[i];
            if(words_mask == (1 << 26) - 1) {
                return (1 << 26) - 1;
            }
        }
    }
    return words_mask;
}

int usable_subsets(uint mask, int index) {
    if(mask == 0) {
        return 0;
    }
    
    if(or_mask(mask) == (1 << 26) - 1) {
        uint amount = 0;
        for(; index < 26; ++index) {
            uint subset_mask = mask & (~(1 << index));
            if(subset_mask != mask) {
                amount += usable_subsets(subset_mask, index);
            }
        }
        return amount + 1;
    }
    return 0;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    std::cin >> words_len;
    
    std::string word;
    for(int w = 0; w < words_len; ++w) {
        std::cin >> word;
        for(char c : word) {
            words[w] |= (1 << (c - 'a'));
        }
    }
    std::cout << usable_subsets((1 << words_len) - 1, 0) << std::endl;
}


// #include <iostream>
// #include <cstdint>
// 
// using uint = uint32_t;
// 
// int words_len = 0;
// uint words[25];
// 
// uint or_mask(uint mask) {
//     uint words_mask = 0;
//     for(uint i = 0; i < words_len; ++i) {
//         if((mask & (1 << i)) != 0) {
//             words_mask |= words[i];
//             if(words_mask == (1 << 26) - 1) {
//                 return (1 << 26) - 1;
//             }
//         }
//     }
//     return words_mask;
// }
// 
// int usable_subsets() {
//     int amount = 0;
//     int max_mask = 1 << words_len;
//     for(uint mask = 0; mask < max_mask; ++mask) {
//         if(or_mask(mask) == (1 << 26) - 1) {
//             ++amount;
//         }
//     }
//     return amount;
// }
// 
// int main() {
//     std::cin.sync_with_stdio(false);
//     std::cout.sync_with_stdio(false);
//     std::cin >> words_len;
//     
//     std::string word;
//     for(int w = 0; w < words_len; ++w) {
//         std::cin >> word;
//         for(char c : word) {
//             words[w] |= (1 << (c - 'a'));
//         }
//     }
//     std::cout << usable_subsets() << std::endl;
// }
