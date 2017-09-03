#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    std::vector<std::string> words;
    
    while(true) {
        std::string word;
        std::cin >> word;
        if(std::cin.eof()) {
            break;
        }
        words.emplace_back(std::move(word));
    }
    std::vector<std::string> compound_words;
    compound_words.reserve(words.size() * words.size());
    
    for(int i = 0; i < words.size(); ++i) {
        for(int j = i + 1; j < words.size(); ++j) {
            std::string compound = words[i] + words[j];
            auto it = std::find(std::begin(compound_words), std::end(compound_words), compound);
            if(it == std::end(compound_words)) {
                compound_words.emplace_back(std::move(compound));
            }
            
            std::string compound2 = words[j] + words[i];
            auto it2 = std::find(std::begin(compound_words), std::end(compound_words), compound2);
            if(it2 == std::end(compound_words)) {
                compound_words.emplace_back(std::move(compound2));
            }
        }
    }
    std::sort(std::begin(compound_words), std::end(compound_words));
    for(std::string& compound : compound_words) {
        std::cout << compound << std::endl;
    }
}
