#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>

struct C {
    int weight;
    std::string name;
};

int candidates_len;
C candidates[11];

int finalists_len;
C finalists[44];

bool first_rodeo = true;

int name[26];

int sum(C* people, int people_len, int mask, int max_sum, int& len) {
    int res = 0;
    
    for(int i = 0; i < people_len; ++i) {
        if(((1 << i) & mask) != 0) {
            len += 1;
            
            res += people[i].weight;
            if(res > max_sum) {
                return -1;
            }
        }
    }
    return res;
}

int best_mask(C* people, int people_len, int max_sum, int max_len) {
    int best_weight = -1;
    int best_mask = -1;
    int best_len = 9999;
    
    int mask_limit = 1 << (people_len + 1);
    for(int mask = 1; mask < mask_limit; ++mask) {
        int len = 0;
        int w = sum(people, people_len, mask, max_sum, len);
        if(len > max_len) {
            continue;
        }
        
        if((w > best_weight) || (w == best_weight && len < best_len)) {
            best_weight = w;
            best_mask = mask;
            best_len = len;
        }
    }
    return best_mask;
}

std::vector<C> get_from_mask(C* people, int people_len, int mask) {
    std::vector<C> result;
    for(int i = candidates_len - 1; i >= 0; --i) {
        if(((1 << i) & mask) != 0) {
            result.push_back(people[i]);
        }
    }
    return result;
}

int main() {
    while(true) {
        memset(name, 0, sizeof(name));
        finalists_len = 0;
        
        int regions;
        int max_weight;
        if(scanf("%d %d", &regions, &max_weight) != 2) {
            return 0;
        } else {
            if(!first_rodeo) {
                puts("");
            }
            first_rodeo = false;
        }

        for(int r = 0; r < regions; ++r) {
            scanf("%d", &candidates_len);
            for(int i = 0; i < candidates_len; ++i) {
                scanf("%*c");
                char initial;
                scanf("%c", &initial);
                candidates[i].name = initial;
            }
            
            for(int i = 0; i < candidates_len; ++i) {
                scanf("%d", &candidates[i].weight);
            }
            
            std::reverse(std::begin(candidates), std::begin(candidates) + candidates_len);
            
            printf("representative for region%d: ", r + 1);
            
            int mask = best_mask(candidates, candidates_len, max_weight, 3);
            std::vector<C> winners = get_from_mask(candidates, candidates_len, mask);
            
            for(int i = 0; i < winners.size(); ++i) {
                int count = name[winners[i].name[0] - 'A']++;
                if(count != 0) {
                    winners[i].name += std::to_string(r + 1);
                }

                finalists[finalists_len++] = winners[i];
                
                if(i == winners.size() - 1) {
                    printf("%s\n", winners[i].name.c_str());
                } else {
                    printf("%s ", winners[i].name.c_str());
                }
            }
        }
        
        std::reverse(std::begin(finalists), std::begin(finalists) + finalists_len);
        
        printf("Leaders: ");
        int mask = best_mask(finalists, finalists_len, max_weight + 100, 4);
        std::vector<C> winners = get_from_mask(finalists, finalists_len, mask);
        
        for(int i = 0; i < winners.size(); ++i) {
            if(i == winners.size() - 1) {
                printf("%s\n", winners[i].name.c_str());
            } else {
                printf("%s ", winners[i].name.c_str());
            }
        }
    }
}
