#include <stdio.h>

int main()
{
	int p=6;
	printf("%d ",p%2);
	printf("%d ",(p>>1)%2);
	printf("%d ",(p>>2)%2);
	return 0;
}