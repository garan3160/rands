#include <stdio.h>

int main()
{
	for(int i = 0; i < 255; i++)
	{
		printf("%c | %02x | %d, ", i, i, i);
	}

	return 0;
}

