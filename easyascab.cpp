#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

int after[26];
string a[1000];
char outAlpha[26];

void compare(int i) {
	for(int x = 0; x < a[i].length(); x++) {
		const char c1 = a[i][x];
		const char c2 = a[i + 1][x];
		
		if(c1 != c2) {
			after[c2 - 'a'] |= 1 << (c1 - 'a');
			return;
		}
	}
}

void p(char a, int alphaLen) {
	bitset<4> b(after[a - 'a']);
	cout << b << std::endl;
	cout << a << " comes after: " << std::endl;
	
	if(after[a - 'a'] == -1) {
		cout << "\tdone\n";
		return;
	}
	
	for(int i = 0; i < alphaLen; ++i) {
		if((after[a - 'a'] & (1 << i)) != 0) {
			cout << '\t' << (char)(i + 'a') << std::endl;
		}
	}
	cout << std::endl;
}

int main() {
	cout.sync_with_stdio(false);
	char c;
	int len;
	std::cin >> c >> len;
	
	int alphaLen = 1 + (c - 'a');
	
	for(int i = 0; i < len; ++i) {
		cin >> a[i];
	}
	
	for(int i = 0; i < len - 1; ++i) {
		compare(i);
	}
	
	for(int i = 0; i < alphaLen; i++) {
		// Find the next char without a char after it
		int j = -1;
		for(int x = 0; x < alphaLen; x++) {
			if(after[x] == 0) {
				// We already found one that doesn't have a char after it
				// We found an ambiguous case
				if(j != -1) {
					cout << "AMBIGUOUS\n";
					return 0;
				}
				j = x;
				after[x] = -1;
			}
		}
		if(j == -1) {
			cout << "IMPOSSIBLE\n";
			return 0;
		}
		
		outAlpha[i] = (char)(j + 'a');
		
		for(int y = 0; y < alphaLen; ++y) {
			if(after[y] != -1) {
				after[y] &= ~(1 << j);
			}
		}
	}
	for(int i = 0; i < alphaLen; ++i) {
		cout << outAlpha[i];
	}
	cout << '\n';
}