#ifndef _MYMALLOC_H
#define _MYMALLOC_H
	
	/*
	 * static array of size 4096 to represent memory to be allocated
	 */
	static char mem[4096]; 

	/*
	 * structure to store metadata for mymalloc() and myfree()
	 */
	typedef struct _metadata
	{
		unsigned short in_use: 1;
		unsigned short size: 13;
	} metadata;

	/* 
	 * function interpositions for malloc() -> mymalloc() and free() -> myfree()
	 */
	#define malloc(s, file, line) mymalloc(s, file, line)
	#define free(ptr, file, line) myfree(ptr, file, line)

	/*
	 * function signatures
	 */
	void* mymalloc(size_t, char*, int);
	int myfree(void*, char*, int);

	#endif
