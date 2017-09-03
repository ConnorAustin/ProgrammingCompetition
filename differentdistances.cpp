#include <cmath>
#include <cstdio>
#include <cstdlib>

int main() 
{
	double x1, y1, x2, y2, p;
	while(scanf("%lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &p) == 5) 
	{
		double xdiff = std::abs(x1 - x2);
		double ydiff = std::abs(y1 - y2);
		
		double dist = pow(pow(xdiff, p) + pow(ydiff, p), 1.0 / p);
		printf("%f\n", dist);
	}
}