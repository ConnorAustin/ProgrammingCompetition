#include <cstdio>
#include <vector>

int graph[20][20];
int vertices;

std::vector<int> get_neighbors(int vertex) {
    std::vector<int> neighbors;
    for(int x = 0; x < vertices; ++x) {
        if(graph[vertex][x]) {
            neighbors.push_back(x);
        }
    }
    return neighbors;
}

int main() {
    while(true) {
        scanf("%d", &vertices);
        
        if(vertices == -1) {
            break;
        }
        
        for(int y = 0; y < vertices; ++y)
        for(int x = 0; x < vertices; ++x) {
            scanf("%d", &graph[x][y]);
        }
        
        for(int x = 0; x < vertices; ++x) {
            bool is_triangle = false;
            auto neighbors = get_neighbors(x);
            for(int neighbor : neighbors) {
                auto neighbors_of_neighbor = get_neighbors(neighbor);
                
                for(int n : neighbors_of_neighbor) {
                    for(int nn : neighbors) {
                        if(n == nn) {
                            is_triangle = true;
                            break;
                        }
                    }
                }
            }
            if(!is_triangle) {
                printf("%d ", x);
            }
        }
        puts("");
    }
}