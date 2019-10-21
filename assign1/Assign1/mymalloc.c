#include <stdio.h>
#include "mymalloc.h"

// mem will hold all user-accessible memory space.
// We initialize it as empty to make sure there isn't any gibberish in it.
static char mem[4096] = {'\0'};

int firstTime = 1;

void* mymalloc(size_t req_size, char* file, int line)
{
	/* Error: users requests to allocate 0 memory */
	if(req_size <= 0)
	{
		fprintf(stderr, ERR_STR, file, line, "cannot allocate <= 0 bytes\n");
		return NULL;
	}
	if(firstTime == 1)
	{
		// This is our first ever memory allocation, so let's
		// set firstTime to 0 and make our first block!
		firstTime = 0;
		metadata block = {0, 4096-SIZE_META};
		*(metadata *)(mem + 0) = block;
	};

	if(req_size > 4096-SIZE_META)
	{
		fprintf(stderr, ERR_STR, file, line, MEM_FULL);
		return NULL;
	}

	int index = 0;
	while(index < 4096)
	{
		int in_use = ((metadata*)(mem + index))->in_use;
		int size = ((metadata*)(mem + index))->size;

		if(in_use  == 0)
		{
			if(size >= req_size + SIZE_META)
			{
				// Allocate memory as requested.
				((metadata*)(mem + index))->in_use = 1;
				((metadata*)(mem + index))->size = req_size;
				void* ptr = (mem + (index + SIZE_META));
				if(size > req_size && size-req_size >= SIZE_META)
				{
					metadata block = {0, size-req_size-SIZE_META};
					*(metadata *)(mem + index + SIZE_META + req_size) = block;
				}
				// *(mem + index + SIZE_META) = 'K';
				return ptr;
			}
			/* not enough available space */
			else
			{
				index += (SIZE_META + size);
				continue;
			}
		}
		index += (SIZE_META + size);
	}
	fprintf(stderr, ERR_STR, file, line, NO_SPACE);
	return NULL;
}

void myfree(void* ptr, char* file, int line)
{

	if(ptr == NULL)
	{
		fprintf(stderr, ERR_STR, file, line, FR_NULL);
	}
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
		index += SIZE_META;
		if(mem + index == ptr && in_use == 1)
		{
			success = 1;
			index -= SIZE_META;
			((metadata*)(mem + index))->in_use = 0;
			// previous metadata not in use
			if(prev != -1 && ((metadata*)(mem + index - prev_size - SIZE_META))->in_use == 0)
			{
				prev_free = 1;
			}
			// next metadata is not in use. get size of next free block of mem.
			if(index + SIZE_META + size < 4096 - SIZE_META && ((metadata*)(mem + index + SIZE_META + size))->in_use == 0)
			{
				next_free = 1;
				next_size = ((metadata*)(mem + index + SIZE_META + size))->size;
			}

			if(index + SIZE_META + size == 4094)
			{
				next_free = 1;
				next_size = 2;
			}
			if(index + SIZE_META + size == 4095)
			{
				next_free = 1;
				next_size = 1;
			}
			
			if(prev_free == 1 && next_free == 0)
			{
				// Set the size of the previous block to prev_size + SIZE_META + size.
				((metadata*)(mem + index - prev_size - SIZE_META))->size = prev_size + SIZE_META + size;
			}
			if(prev_free == 1 && next_free == 1)
			{
				// Set the size of the previous block to prev_size + size + next_size.
				((metadata*)(mem + index - prev_size - SIZE_META))->size = prev_size + SIZE_META + size + SIZE_META + next_size;
			}
			if(prev_free == 0 && next_free == 1)
			{
				// Set the size of the current block to size + SIZE_META + next_size.
				((metadata*)(mem + index))->size = size + SIZE_META + next_size;
			}
			return;
		}
		else
		{
			prev = index - SIZE_META;
			prev_size = size;
			index += size;
		}
	}

	if(success == 0)
	{
		fprintf(stderr, ERR_STR, file, line, PTR_DNE);
	}
}
