#include <stdio.h>
#include "mymalloc.h"

<<<<<<< HEAD
int firstTime = 1;

void* mymalloc(size_t req_size, char* file, int line)
{
	// printf("mymalloc called in file %s on line %d\n", file, line);

	if(firstTime == 1)
	{
		// This is our first ever memory allocation, so let's
		// set firstTime to 0 and make our first block!
		firstTime = 0;
		metadata block = {0, 4096-sizeof(metadata)};
		*(metadata *)(mem + 0) = block;
	};
	
	int index = 0;
	while(index < 4096)
	{
		int in_use = ((metadata*)(mem + index))->in_use;
		int size = ((metadata*)(mem + index))->size;
		// printf("block %d\n", index);

		if(in_use  == 0)
		{
			// printf("not in use\n");
			if(size >= req_size){
				// Allocate memory as requested.
				((metadata*)(mem + index))->in_use = 1;
				((metadata*)(mem + index))->size = req_size;
				void* ptr = mem + index + sizeof(metadata);
				if(size > req_size)
				{
					metadata block = {0, size-sizeof(metadata)-req_size-sizeof(metadata)};
					*(metadata *)(mem + index + sizeof(metadata) + req_size) = block;
				}
				printf("Success! %zu bytes allocated at block %lu\n", req_size, index + sizeof(metadata));
				*(mem + index + sizeof(metadata)) = 'K';
				return ptr;
			}
		}

		index += (sizeof(metadata) + size);
		// printf("Next, we'll look at block %d\n", index);
	}

	printf("malloc(%zu) failed on %s:%d\n", req_size, file, line);

=======
void* mymalloc(size_t s, char* file, int line)
{
	printf("mymalloc called on line %d in file %s\n", line, file);
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a
	return NULL;
}

int myfree(void* ptr, char* file, int line)
{
<<<<<<< HEAD
	// printf("myfree called in file %s on line %d\n", file, line);
=======
	printf("myfree called on line %d in file %s\n", line, file);
>>>>>>> 97ceddd4fc967859485689d2094619db0d099f6a
	return 0;
}
