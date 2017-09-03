#include <iostream>

int main() 
{
	int cases;
	std::cin >> cases;
	
	for(int c = 0; c < cases; ++c) 
	{
		std::string line1, line2;
		std::cin >> line1 >> line2;
		
		std::cout << line1 << std::endl;
		std::cout << line2 << std::endl;
		for(int i = 0; i < line1.length(); ++i) 
		{
			if(line1[i] == line2[i]) 
				std::cout << '.';
			else
				std::cout << '*';
		}
		std::cout << std::endl << std::endl;
	}
}