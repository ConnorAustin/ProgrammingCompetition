#include <iostream>
#include <vector>

std::vector<char> adrian = {{'A', 'B', 'C'}};
std::vector<char> bruno = {{'B', 'A', 'B', 'C'}};
std::vector<char> goran = {{'C', 'C', 'A', 'A', 'B', 'B'}};

int getPoints(const std::vector<char>& answersGiven, const std::string& answers)
{
	int points = 0;
	for(int i = 0; i < answers.length(); ++i) 
	{
		if(answersGiven[i % answersGiven.size()] == answers[i]) 
			++points;
	}
	return points;
}

int main()
{
	int junk;
	std::string answers;
	std::cin >> junk >> answers;
	
	int adrianPoints = getPoints(adrian, answers);
	int brunoPoints = getPoints(bruno, answers);
	int goranPoints = getPoints(goran, answers);
	int maxPoints = std::max(std::max(adrianPoints, brunoPoints), goranPoints);
	
	std::cout << maxPoints << std::endl;
	
	if(adrianPoints == maxPoints) 
		std::cout << "Adrian" << std::endl;
		
	if(brunoPoints == maxPoints) 
		std::cout << "Bruno" << std::endl;
		
	if(goranPoints == maxPoints) 
		std::cout << "Goran" << std::endl;
}