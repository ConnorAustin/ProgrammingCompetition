#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>

#define u64 uint64_t

u64 cities;
u64 graph[30 * 30];
u64 dists[30 * 30];

void floyd_warshall() {
    for(int k = 0; k < cities; ++k) {
        for(int i = 0; i < cities; ++i) {
            for(int j = 0; j < cities; ++j) {
                dists[i * cities + j] = 
                    std::min(dists[i * cities + j], 
                             dists[i * cities + k] + dists[k * cities + j]);
            }
        }
    }
}

int main() {
    while(true) {
        std::cin >> cities;
        if(std::cin.eof()) {
            return 0;
        }
        
        for(int i = 0; i < cities - 1; ++i) {
            graph[i * cities + i] = 0;
            dists[i * cities + i] = 0;
            
            for(int j = i + 1; j < cities; ++j) {
                std::string dist;
                std::cin >> dist;
                
                graph[i * cities + j] = atoi(dist.c_str());
                graph[j * cities + i] = graph[i * cities + j];
                
                dists[i * cities + j] = graph[i * cities + j];
                dists[j * cities + i] = graph[i * cities + j];
            }
        }
        graph[(cities - 1) * cities + (cities - 1)] = 0;
        dists[(cities - 1) * cities + (cities - 1)] = 0;
        
        floyd_warshall();
        
        u64 max_dist = 0;
        for(int i = 0; i < cities; ++i) {
            for(int j = 0; j < cities; ++j) {
                max_dist = std::max(max_dist, dists[i * cities + j]);
            }
        }
        
        std::cout << "The maximal shortest path takes " << max_dist << " minutes." << std::endl;
    }    
}
