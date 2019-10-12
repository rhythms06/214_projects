#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("size of int: %d\n", sizeof(int));
	printf("size of short: %d\n", sizeof(short));
	printf("size of unsigned int: %d\n", sizeof(unsigned int));
	printf("size of unsigned short: %d\n", sizeof(unsigned short));

	typedef struct _metadata
	{
		unsigned short in_use: 1;
		unsigned short size: 13;
	} metadata;

	metadata bitfield_test = {1, 4095};
	printf("size of bitfield_test: %d\n", sizeof(bitfield_test));

	char memory[4096] = {'\0'};

	*(metadata *)(memory + 0) = bitfield_test;

	int i = 0;
	while(i < 16)
	{
		printf("memory[%u]: %u\n", i, ((metadata*)(memory + i))->in_use);
		printf("memory[%u]: %u\n", i, ((metadata*)(memory + i))->size);
		memory[i] = 0;
		i++;
	}

	return 0;
}
