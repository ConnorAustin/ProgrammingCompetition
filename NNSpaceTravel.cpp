#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <iterator>

int matrix[30][30];
int res_matrix[30][30];

int unique_index = 0;
std::map<std::string, int> planet_indexer;

std::vector<std::string> split(const std::string& str) {
    std::vector<std::string> result;
    int begin = 0;
    int end = str.find(' ');
    result.push_back(str.substr(begin, end - begin));
    
    while(end != std::string::npos) {
        begin = end;
        end = str.find(' ', begin + 1);
        result.push_back(str.substr(begin + 1, end - begin - 1));
    }
    return result;
}

int get_index(const std::string& planet) {
    auto pair = planet_indexer.find(planet);
    if(pair == std::end(planet_indexer)) {
        planet_indexer[planet] = unique_index;
        return unique_index++;
    }
    return pair->second;
}

std::string get_name(int index) {
    for(const auto& pair : planet_indexer) {
        if(pair.second == index) {
            return pair.first;
        }
    }
    return "";
}

void square(int planets) {
    int tmp_matrix[30][30];
    memcpy(tmp_matrix, res_matrix, sizeof(res_matrix));
    
    for(int y = 0; y < planets; ++y) {
        for(int x = 0; x < planets; ++x) {
            int result = 0;
            for(int i = 0; i < planets; ++i) {
                result += tmp_matrix[y][i] * matrix[i][x];
            }
            res_matrix[y][x] = result > 0;
        }
    }
}

std::vector<std::string> grab_names(int planets, const std::string& starting_planet) {
    std::vector<std::string> names;
    int index = get_index(starting_planet);
    for(int p = 0; p < planets; ++p) {
        if(res_matrix[index][p] != 0) {
            names.push_back(get_name(p));
        }
    }
    return names;
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    while(true) {
        int planets, mappings;
        std::cin >> planets >> mappings;
        if(std::cin.eof()) {
            break;
        }
        unique_index = 0;
        planet_indexer.clear();
        
        memset(matrix, 0, sizeof(matrix));
        
        std::string line;
        std::getline(std::cin, line); // junk newline
        for(int m = 0; m < mappings; ++m) {
            std::getline(std::cin, line);
            std::vector<std::string> words = split(line);

            int index = get_index(words[0]);
            for(int i = 2; i < words.size(); ++i) {
                int index2 = get_index(words[i]);
                matrix[index][index2] = 1;
                matrix[index2][index] = 1;
            }
        }
        memcpy(res_matrix, matrix, sizeof(res_matrix));

        int travels;
        std::string starting_planet;
        std::cin >> travels >> starting_planet;
        
        for(int i = 0; i < travels + 1; ++i) {
           square(planets);
        }
        
        std::cout << "Visit: ";
        std::vector<std::string> names = grab_names(planets, starting_planet);
        for(int i = 0; i < names.size(); ++i) {
            std::cout << names[i];
            if(i != names.size() - 1) {
                std::cout << ' ';
            }
        }
        
        std::cout << std::endl;
    }
}