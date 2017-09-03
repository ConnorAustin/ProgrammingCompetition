#include <iostream>
#include <vector>
#include <algorithm>

int numDistances;
int distances[200000];

bool reachableHole[200001];

void findPossibles() {
    for(int x = 0; x < numDistances; ++x) {
        reachableHole[distances[x]] = true;
        
        for(int y = x; y < numDistances; ++y) {
            int dist = distances[x] + distances[y];
            if(dist <= 200000) {
                reachableHole[distances[x] + distances[y]] = true;
            }
        }
    }
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    
    std::cin >> numDistances;
    for(int d = 0; d < numDistances; ++d) {
        std::cin >> distances[d];
    }
    
    findPossibles();
    
    int numHoles;
    std::cin >> numHoles;
    
    int completed = 0;
    for(int h = 0; h < numHoles; ++h) {
        int hole;
        std::cin >> hole;
        
        if(reachableHole[hole]) {
            ++completed;
        }
    }
    
    std::cout << completed << std::endl;
}
