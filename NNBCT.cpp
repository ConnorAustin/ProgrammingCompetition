#include <iostream>
#include <cstdlib>
#include <cstring>

int graph[30 * 30];
int dists[30];
bool marked[30];
int cities;

int min_city() {
    int min = -1;
    int city = -1;
    
    for(int i = 0; i < cities; ++i) {
        if(!marked[i] && dists[i] != -1 && (min == -1 || dists[i] < min)) {
            min = dists[i];
            city = i;
        }
    }
    return city;
}

void djikstra() {
    memset(dists, -1, sizeof(int) * cities);
    memset(marked, false, sizeof(bool) * cities);
    dists[0] = 0;
    
    for(int i = 0; i < cities - 1; ++i) {
        int j = min_city();
        if(j == -1) {
            return;
        }
        
        marked[j] = true;
        
        for(int v = 0; v < cities; ++v) {
            if(!marked[v] && graph[v * cities + j] != -1) {
                int d = dists[j] + graph[v * cities + j];
                if(dists[v] == -1 || dists[v] > d) {
                    dists[v] = d;
                    if(v == cities - 1) {
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    std::cin.sync_with_stdio(false);
    std::cout.sync_with_stdio(false);
    std::string line;
    
    while(true) {
        std::cin >> cities;
        if(std::cin.eof()) {
            return 0;
        }
        
        memset(graph, -1, sizeof(int) * cities * cities);
        
        for(int i = 0; i < cities - 1; ++i) {
            graph[i * cities + i] = 0;
            
            for(int j = i + 1; j < cities; ++j) {
                std::string dist;
                std::cin >> dist;
                if(dist != "X") {
                    graph[i * cities + j] = atoi(dist.c_str());
                    graph[j * cities + i] = graph[i * cities + j];
                }
            }
        }
        graph[(cities - 1) * cities + (cities - 1)] = 0;
        
        djikstra();
        
        int dist = dists[cities - 1];
        if(dist == -1) {
            std::cout << "There is currently no path available." << std::endl;
        } else {
            std::cout << "The shortest path will take " << dist << " minutes." << std::endl;
        }
    }
}
