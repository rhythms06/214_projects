#ifndef _MYMALLOC_H
#define _MYMALLOC_H

	// mem will hold all user-accessible memory space.
	// We initialize it as empty to make sure there isn't any gibberish in it.
	static char mem[4096] = {'\0'};

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
	void myfree(void*, char*, int);

	#endif
