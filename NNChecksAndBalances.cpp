#include <cstdio>
#include <bitset>

int checks[15];
int checks_len;
int desired_sum;
bool done;

void print_correct_multiverse(std::bitset<15> include) {
    bool first_print = true;
    for(int c = 0; c < checks_len; ++c) {
        if(include.test(c)) {
            if(first_print) {
                printf("%d", checks[c]);
                first_print = false;
            } else {
                printf(" %d", checks[c]);
            }
        }
    }
    puts("");
}

void multiverse_sum(int index, std::bitset<15> include, int sum) {
    if(done) {
        return;
    }
    
    if(sum == desired_sum) {
        done = true;
        print_correct_multiverse(include);
        return;
    }
    
    if(index == checks_len) {
        return;
    }
    
    multiverse_sum(index + 1, include, sum);
    
    include.set(index);
    multiverse_sum(index + 1, include, sum + checks[index]);
}

int main() {
    int cases;
    scanf("%d", &cases);
    
    for(int c = 0; c < cases; ++c) {
        int ledger, bank;
        scanf("%d %d %d", &ledger, &bank, &checks_len);
        
        for(int i = 0; i < checks_len; ++i) {
            scanf("%d", &checks[i]);
        }
        
        done = false;
        desired_sum = bank - ledger;
        multiverse_sum(0, 0, 0);
        if(!done) {
            puts("Bank Error");
        }
    }
}
