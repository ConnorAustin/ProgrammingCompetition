#include <iostream>
#include <algorithm>

std::string students[200];

int main() {
    int students_len;
    while(std::cin >> students_len, students_len != 0) {
        for(int s = 0; s < students_len; ++s) {
            std::cin >> students[s];
        }
        
        std::stable_sort(std::begin(students), std::begin(students) + students_len, [](const std::string& a, const std::string& b) {
            if(a[0] == b[0]) {
                return a[1] < b[1];
            }
            return a[0] < b[0];
        });
        
        for(int i = 0; i < students_len; ++i) {
            std::cout << students[i] << std::endl;
        }
        std::cout << std::endl;
    }
}