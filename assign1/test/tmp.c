#include <stdio.h>
#include <stdlib.h>

int main()
{
<<<<<<< HEAD
	printf("size of int: %lu\n", sizeof(int));

	printf("size of short: %lu\n", sizeof(short));

	struct s {
		char inuse;
		short prev;
		short size;
	};

	struct s S = {'t', 0, 500};

	printf("size of S: %lu\n", sizeof(S));

	printf("size of unsigned int: %lu\n", sizeof(unsigned int));

	printf("size of unsigned short: %lu\n", sizeof(unsigned short));
=======
	printf("size of int: %d\n", sizeof(int));
	printf("size of short: %d\n", sizeof(short));
	printf("size of unsigned int: %d\n", sizeof(unsigned int));
	printf("size of unsigned short: %d\n", sizeof(unsigned short));
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a

	typedef struct _metadata
	{
		unsigned short in_use: 1;
		unsigned short size: 13;
	} metadata;

	metadata bitfield_test = {1, 4095};
<<<<<<< HEAD



	printf("size of bitfield_test: %lu\n", sizeof(bitfield_test));
=======
	printf("size of bitfield_test: %d\n", sizeof(bitfield_test));
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a

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
<<<<<<< HEAD
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
=======
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a

	return 0;
}
