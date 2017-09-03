#include <iostream>
#include <cmath>

using namespace std;

struct rect {
	int w, h;
	
	void read() {
		cin >> w >> h;
	}
	
	rect rotate() {
		rect r;
		r.w = h;
		r.h = w;
		return r;
	}
};

bool tryFit(rect a, rect b, rect freeSpace) {
	return (a.w == b.w && a.w == freeSpace.w && a.h + b.h == freeSpace.h) || 
		(a.h == b.h && a.h == freeSpace.h && a.w + b.w == freeSpace.w);
}

bool fits(rect a, rect b, rect freeSpace) {
	return 
		tryFit(a,          b,          freeSpace) || 
		tryFit(a.rotate(), b,          freeSpace) || 
		tryFit(a,          b.rotate(), freeSpace) ||
		tryFit(a.rotate(), b.rotate(), freeSpace);
}

bool fits(rect a, rect b, rect c, int x) {
	rect freeSpace;
	freeSpace.w = x;
	freeSpace.h = x;
	
	if(a.w == x) {
		freeSpace.h -= a.h;
		return fits(b, c, freeSpace);
	}
	else if(a.h == x) {
		freeSpace.w -= a.w;
		return fits(b, c, freeSpace);
	}
	else return false;
}

int main() {
	rect a, b, c;
	a.read();
	b.read();
	c.read();
	
	int area = a.w * a.h + b.w * b.h + c.w * c.h;
	
	for(int x = 1; x < area; ++x) {
		if(x * x == area) {
			if(fits(a, b, c, x) || fits(b, a, c, x) || fits(c, a, b, x)) {
				cout << "YES\n";
				return 0;
			}
		}
	}
	cout << "NO\n";
}