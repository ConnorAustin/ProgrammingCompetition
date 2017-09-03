#include <iostream>

using namespace std;
using i64 = long long;

i64 nums[10];
i64 x;
int n;

bool iterate() {
	x += nums[n - 1];
	
	nums[0] = nums[1] - nums[0];
	
	i64 first = nums[0];
	
	bool constant = true;
	for(int i = 1; i < n - 1; ++i) {
		nums[i] = nums[i + 1] - nums[i];
		if(nums[i] != first) {
			constant = false;
		}
	}
	--n;
	
	if(constant)
		x += first;
		
	return !constant;
}

int main() {	
	cin >> n;
	int origN = n;

	for(int i = 0; i < n; ++i)
		cin >> nums[i];
	
	while(iterate());
	
	cout << origN - n << ' ' << x << endl;
}

/*
9    25    49    81     x
  a      a    32    x - 81
     8    8    8 + 81 + 32 = x
*/