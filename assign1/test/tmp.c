#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("size of int: %d\n", sizeof(int));

	printf("size of short: %d\n", sizeof(short));

	struct s {
		char inuse;
		short prev;
		short size;
	};

	struct s S = {'t', 0, 500};

	printf("size of S: %d\n", sizeof(S));

	printf("size of unsigned int: %d\n", sizeof(unsigned int));

	printf("size of unsigned short: %d\n", sizeof(unsigned short));

	//unsigned short in_use: 1 = 0;
	//printf("size of in_use: %d\n", sizeof(in_use));

	typedef struct _metadata
	{
		unsigned short in_use: 1;
		//unsigned short prev: 13;
		unsigned short size: 13;
	} metadata;




	metadata bitfield_test = {1, 4095};



	printf("size of bitfield_test: %d\n", sizeof(bitfield_test));



	char memory[4096] = {'\0'};

	*(metadata *)(memory + 0) = bitfield_test;
//	printf("%d\n", memory[0].in_use);

	memory[5] = 'a';
	//printf("(memory + 1): %d\n", (memory + 1));

	int i = 0;
	while(i < 16)
	{
		printf("memory[%u]: %u\n", i, ((metadata*)(memory + i))->in_use);
		printf("memory[%u]: %u\n", i, ((metadata*)(memory + i))->size);
		printf("(memory + %u): %u\n", i, (memory + i));
		memory[i] = 0;
		i++;
	}
/*
	i = 0;
	
	while(i < 16)
	{
		printf("memory[i]: %d\n", memory[i]);
		i++;
	}
*/
/*
	printf("memory[0]: %%c -> %c\n", memory[0]);
	printf("memory[0]: %%d -> %d\n", memory[0]);
	printf("(memory + 0): %%c -> %c\n", (memory + 0));
	printf("(memory + 0): %%s -> %s\n", (memory + 0));
	printf("(memory + 1): %%c -> %c\n", (memory + 1));
*/

/*
	memory[0] = (char)500;
	printf("memory[0]: %d\n", memory[0]);
	printf("memory[1]: %d\n", memory[1]);
*/

	return 0;
}
