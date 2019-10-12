#ifndef _MYMALLOC_H
#define _MYMALLOC_H

	// static array of size 4096 to represent memory to be allocated
	static char mem[4096];

	typedef struct _metadata
	{
		unsigned short in_use: 1;
		unsigned short size: 13;
	} metadata;

	/* macro that will replace all calls to malloc(x) with calls to
	 * mymalloc(x)
	 * */
	#define malloc(size) mymalloc(size, __FILE__, __LINE__)

	/* macro that will replace all calls to free(x) to myfree(x) */
	#define free(ptr) myfree(ptr, __FILE__, __LINE__)

	/* function signature for mymalloc(x) which will be written in
	 * mymalloc.c
	* */
	void* mymalloc(size_t, char*, int);

	/* function signature for myfree(x) which will be written in
	 * mymalloc.c
	 * */
	int myfree(void*, char*, int);

	#endif
