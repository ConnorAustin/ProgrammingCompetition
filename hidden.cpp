#include <cstdio>
#include <cstring>

char password[9];
char message[41];

int main() {
    scanf("%s %s", password, message);
    
    int password_len = strlen(password);
    int message_len = strlen(message);
    
    int password_index = 0;
    for(int i = 0; i < message_len; ++i) {
        for(int p = password_index; p < password_len; ++p) {
            if(password[p] == message[i]) {
                if(p == password_index) {
                    ++password_index;
                    if(password_index == password_len) {
                        puts("PASS");
                        return 0;
                    }
                    break;
                } else {
                    puts("FAIL");
                    return 0;
                }
            }
        }
    }
    puts("FAIL");
}
