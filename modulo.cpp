#include <cstdio>

int contains[42];

int main() {
    for(int i = 0; i < 10; ++i) {
        int number;
        scanf("%d", &number);
        contains[number % 42] = 1;
    }
    
    int numbers = 0;
    for(int i = 0; i < 42; ++i) {
        numbers += contains[i];
    }
    
    printf("%d\n", numbers);
}