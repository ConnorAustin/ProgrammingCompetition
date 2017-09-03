#include <iostream>
#include <cstdio>
#include <cstring>

char bug[1001];
char line[2000001];

int line_len;
int bug_len;

inline int skip(int i) {
    int ii = i;
        
    if(line_len - i < bug_len) {
        return 0;
    }
        
    for(int c = 1; c < bug_len; ++c) {
        if(line[i + c] != bug[c]) {
            if(line[i + c] == bug[0]) {
                i += skip(i + c--);
            } else {
                return 0;
            }
        }
    }
    return i - ii + bug_len;
}

int main() {
    while(true) {
        int line_count;
        if(scanf("%d", &line_count) == 0) {
            break;
        }
            
        scanf("%s", bug);
        bug_len = strlen(bug);
            
        for(int l = 0; l < line_count; ++l) {
            fgets(line, 999999999, stdin);
            line_len = strlen(line);
                
            for(int i = 0; i < line_len; ++i) {
                if(line[i] != bug[0]) {
                    putchar(line[i]);
                } else {
                    int sk = skip(i) - 1;
                    if(sk > 0) {
                        i += sk;
                    } else {
                        putchar(line[i]);
                    }
                }
            }
        }
    }
}
