#include <stdio.h>
#include <stdlib.h>


int main(void)
{

	int* z;
	z=malloc(sizeof(int));
	*z=4;
	printf("%d",*z);
	return 0;
}
