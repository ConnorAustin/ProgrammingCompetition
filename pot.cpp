#include <iostream>
#include <cmath>

int main() 
{
	int numbers;
	std::cin >> numbers;
	
	long X = 0;
	for(int n = 0; n < numbers; ++n) 
	{
		std::string num;
		std::cin >> num;
		int exponent = num[num.length() - 1] - '0';
		num.erase(num.length() - 1, 1);
		int number = std::stoi(num);
		
		int val = 1;
		for(int p = 0; p < exponent; ++p) 
		{
			val *= number;
		}
		X += val;
	}
	std::cout << X << std::endl;
}