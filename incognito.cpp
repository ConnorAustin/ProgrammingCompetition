#include <iostream>
#include <map>

int main() {
    int cases;
    std::cin >> cases;
    for(int c = 0; c < cases; ++c) {
        std::map<std::string, int> categories;
        
        int items;
        std::cin >> items;
        for(int i = 0; i < items; ++i) {
            std::string str;
            std::cin >> str >> str;
            
            auto it = categories.find(str);
            if(it != std::end(categories)) {
                it->second += 1;
            } else {
                categories[str] = 1;
            }
        }

        int disguises = 0;
        for(auto it : categories) {
            disguises += disguises * it.second;
            disguises += it.second;
        }
        
        std::cout << disguises << std::endl;
    }
}