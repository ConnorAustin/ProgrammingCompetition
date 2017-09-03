#include <cstdio>

int main()
{
	int correct[] = {1, 1, 2, 2, 2, 8};
	
	for(int i = 0; i < 6; ++i)
	{
		int amt;
		scanf("%d", &amt);
		
		printf("%d ", correct[i] - amt);
	}
}