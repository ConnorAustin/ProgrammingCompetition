#include <iostream>

using namespace std;
char g[50000][10];

int main() {
	int w, h;
	cin >> h >> w;
	
	std::string line;
	for(int y = 0; y < h; ++y) {
		cin >> line;
		for(int x = 0; x < w; ++x) {
			g[y][x] = line[x];
		}
	}
	
	for(int x = 0; x < w; ++x) {
		int apples = 0;
		for(int y = 0; y < h; ++y) {
			if(g[y][x] == 'a') {
				++apples;
				g[y][x] = '.';
			}
			else if(g[y][x] == '#') {
				for(int a = 0; a < apples; ++a) {
					g[y - a - 1][x] = 'a';
				}
				apples = 0;
			}
			if(y == h - 1) {
				for(int a = 0; a < apples; ++a) {
					g[y - a][x] = 'a';
				}
			}
		}
	}
	
	for(int y = 0; y < h; ++y) {
		for(int x = 0; x < w; ++x) {
			cout << g[y][x];
		}
		cout << '\n';
	}
}