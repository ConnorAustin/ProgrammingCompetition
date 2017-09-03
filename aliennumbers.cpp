#include <iostream>

int get_value(const std::string& language, char c) {
    return (int) language.find(c);
}

int to_base10(const std::string& alien_language, const std::string& alien_number) {
    int number = 0;
    int power = 1;
    int base = alien_language.size();
    for(int i = alien_number.size() - 1; i > -1; --i) {
        number += power * get_value(alien_language, alien_number[i]);
        power *= base;
    }
    return number;
}

int main() {
    int cases;
    std::cin >> cases;
    
    for(int c = 0; c < cases; ++c) {
        std::string alien_number, alien_language, target_language;
        std::cin >> alien_number >> alien_language >> target_language;
        int number = to_base10(alien_language, alien_number);
        
        std::string target_number;
        int base = target_language.size();
        while(number != 0) {
            int rem = number % base;
            number /= base;
            target_number = target_language[rem] + target_number;
        }
        std::cout << "Case #" << c + 1 << ": " << target_number << std::endl;
    }
}