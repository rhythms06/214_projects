#ifndef _MYMALLOC_H
#define _MYMALLOC_H
	

	/* macro that will replace all calls to malloc(x) with calls to
	 * mymalloc(x)
	 * */
	#define malloc(size) mymalloc(size)

	/* macro that will replace all calls to free(x) to myfree(x) */
	#define free(ptr) myfree(ptr)

	/* function signature for mymalloc(x) which will be written in 
	 * mymalloc.c
	* */
	void* mymalloc(size_t);

	/* function signature for myfree(x) which will be written in 
	 * mymalloc.c
	 * */
	int myfree(void*);

	/* define static array of size 4096 to represent memory */
	static char mem[4096]; 

#endif
