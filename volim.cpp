#include <cstdio>

int main() {
    int person, questions;
    scanf("%d %d", &person, &questions);
    int time = 0;
    
    --person;
    for(int q = 0; q < questions; ++q) {
        int time_passed;
        char result;
        scanf("%d %c\n", &time_passed, &result);
        
        time += time_passed;
        if(time >= 210) {
            printf("%d\n", person + 1);
            return 0;
        }
        if(result == 'T') {
            person = (person + 1) % 8;
        }
    }
}
