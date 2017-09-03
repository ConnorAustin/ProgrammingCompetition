#include <iostream>
#include <map>

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    int words, sentences;
    std::cin >> words >> sentences;
    
    std::map<std::string, int> word_value;
    
    std::string word;
    
    for(int w = 0; w < words; ++w) {
        int value;    
        std::cin >> word >> value;
        word_value[word] = value;
    }
    
    for(int s = 0; s < sentences; ++s) {    
        int value = 0;
        while(true) {
            std::cin >> word;
            if(word == ".") {
                break;
            }
            
            auto it = word_value.find(word);
            if(it != std::end(word_value)) {
                value += it->second;
            }
        }
        std::cout << value << std::endl;
    }
}
