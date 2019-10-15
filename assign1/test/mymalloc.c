#include <stdio.h>
#include "mymalloc.h"

// mem will hold all user-accessible memory space.
// We initialize it as empty to make sure there isn't any gibberish in it.
static char mem[4096] = {'\0'};

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

	if(req_size > 4096-sizeof(metadata))
	{
		printf("malloc(%zu) failed on %s:%d. Reason: REQUEST IS LARGER THAN AVAILABLE MEMORY.\n", req_size, file, line);
		return NULL;
	}

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
				// printf("Requested: %zu bytes | Available: %d bytes\n", req_size, size);
				((metadata*)(mem + index))->in_use = 1;
				((metadata*)(mem + index))->size = req_size;
				void* ptr = mem + index + sizeof(metadata);
				// printf("Found an empty block %d bytes long\n", size);
				// printf("Allocated %zu bytes at mem[%lu]\n", req_size, index + sizeof(metadata));
				if(size > req_size && size-req_size >= sizeof(metadata))
				{
					metadata block = {0, size-req_size-sizeof(metadata)};
					*(metadata *)(mem + index + sizeof(metadata) + req_size) = block;
					// printf("Also initialized a free block of size %lu at mem[%lu]\n",
						// size-req_size-sizeof(metadata), index+sizeof(metadata)+req_size+sizeof(metadata));
				}
				// *(mem + index + sizeof(metadata)) = 'K';
				return ptr;
			}
		}

		index += (sizeof(metadata) + size);
		// printf("Next, we'll look at block %d\n", index);
	}

	printf("malloc(%zu) failed on %s:%d. Reason: NO EMPTY BLOCK LARGE ENOUGH TO HOLD REQUESTED BYTES.\n", req_size, file, line);

	return NULL;
}

void myfree(void* ptr, char* file, int line)
{
	// printf("myfree called in file %s on line %d\n", file, line);

	// The starting index of the previous block of metadata.
	int prev = -1;
	// The size of the previous data block.
	int prev_size = 0;
	// Whether or not the previous block is in use.
	// A value of 1 means that it is not in use and can be concatenated with a free block in front of it.
	int prev_free = 0;
	// The current position of mem being examined.
	int index = 0;
	// The size of the next data block.
	int next_size = 0;
	// Whether or not the next block is in use.
	// A value of 1 means that it is not in use and can be concatenated with a free block behind of it.
	int next_free = 0;
	// Whether or not we've found the pointer the user wants to free.
	int success = 0;

	while(index < 4096)
	{
		int in_use = ((metadata*)(mem + index))->in_use;
		int size = ((metadata*)(mem + index))->size;
		index += sizeof(metadata);
		if(mem + index == ptr && in_use == 1)
		{
			success = 1;
			// printf("found the data we wanna free at mem[%d]!\n", index);
			// printf("the previous metadata starts at mem[%lu] and has data size %d!\n", prev + sizeof(metadata), prev_size);

			index -= sizeof(metadata);
			((metadata*)(mem + index))->in_use = 0;
			if(prev != -1 && ((metadata*)(mem + index - prev_size - sizeof(metadata)))->in_use == 0)
			{
				prev_free = 1;
				// printf("the previous metadata is not in use\n");
			}
			if(index + sizeof(metadata) + size < 4096 - sizeof(metadata) && ((metadata*)(mem + index + sizeof(metadata) + size))->in_use == 0)
			{
				next_free = 1;
				next_size = ((metadata*)(mem + index + sizeof(metadata) + size))->size;
				// printf("the next metadata is not in use and has size %d (1)\n", next_size);
			}
			if(index + sizeof(metadata) + size == 4094)
			{
				next_free = 1;
				// printf("the next metadata is not in use (2)\n");
				next_size = 2;
			}
			if(index + sizeof(metadata) + size == 4095)
			{
				next_free = 1;
				// printf("the next metadata is not in use (3)\n");
				next_size = 1;
			}
			if(prev_free == 1 && next_free == 0)
			{
				// Set the size of the previous block to prev_size + sizeof(metadata) + size.
				((metadata*)(mem + index - prev_size - sizeof(metadata)))->size = prev_size + sizeof(metadata) + size;
				// printf("the previous block at mem[%d] now has size %d\n", index - prev_size, prev_size + size);
			}
			if(prev_free == 1 && next_free == 1)
			{
				// Set the size of the previous block to prev_size + size + next_size.
				((metadata*)(mem + index - prev_size - sizeof(metadata)))->size = prev_size + sizeof(metadata) + size + sizeof(metadata) + next_size;
				// printf("the previous block at mem[%d] now has size %lu\n", index - prev_size, prev_size + sizeof(metadata) + size + sizeof(metadata) + next_size);
			}
			if(prev_free == 0 && next_free == 1)
			{
				// Set the size of the current block to size + sizeof(metadata) + next_size.
				((metadata*)(mem + index))->size = size + sizeof(metadata) + next_size;
				// printf("the current block at mem[%lu] now has size %lu\n", index + sizeof(metadata), size + sizeof(metadata) + next_size);
			}
		}
		else
		{
			prev = index - sizeof(metadata);
			prev_size = size;
			index += size;
		}
	}

	if(success == 0)
	{
		printf("free() failed on %s:%d. Reason: POINTER NOT FOUND IN MEMORY.\n", file, line);
	}
}
