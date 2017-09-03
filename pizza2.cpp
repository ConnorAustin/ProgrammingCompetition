#include <cstdio>
#include <cmath>

int main() 
{
	int pizzaRadius, crustSize;
	scanf("%d %d\n", &pizzaRadius, &crustSize);
	
	int cheeseRadius = pizzaRadius - crustSize;
	double cheeseArea = M_PI * cheeseRadius * cheeseRadius;
	double totArea = M_PI * pizzaRadius * pizzaRadius;
	
	printf("%f\n", 100.0 * cheeseArea / totArea);
}