#include <iostream>
#include <vector>

struct Rule {
    std::string ip, action;
};

std::vector<Rule> rules;

int main() {
    int rules_len;
    std::string def_action;
    std::cin >> rules_len >> def_action;
    rules.push_back({"", "Drop"});
    
    std::string junk;
    std::getline(std::cin, junk); // read junk newline
    
    for(int r = 0; r < rules_len; ++r) {
        std::string ip_range;
        std::getline(std::cin, ip_range, '/');
        
        int host;
        std::string action;
        std::cin >> host >> action;
        
        std::cout << ip_range << "..." << host << "..." << action;
    }
}