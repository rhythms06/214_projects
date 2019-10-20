#ifndef _MYMALLOC_H
#define _MYMALLOC_H

	/* used bitfields for optimal metadata */
	typedef struct _metadata
	{
		unsigned short in_use: 1;
		unsigned short size: 13;
		unsigned short : 0; // used for padding unused bits.
	} metadata;

	/* macros that will replace all calls to malloc(x) with calls to mymalloc(x)
	 * and replace all calls to free(x) with myfree(x). */
	#define malloc(size) mymalloc(size, __FILE__, __LINE__)
	#define free(ptr) myfree(ptr, __FILE__, __LINE__)

	/* function signatures. functions written in mymalloc.c library */
	void* mymalloc(size_t, char*, int);
	void myfree(void*, char*, int);

	/* general purpose macros */
	#define SIZE_META sizeof(metadata)

	/* error macros */
	#define ERR_STR "error: %s:%d: error: %s"
	#define MEM_FULL "no available memory\n"
	#define NO_SPACE "insufficient available memory\n"
	#define FR_NULL "attempt to free NULL\n"
	#define PTR_DNE "attempt to free non-allocated memory\n"
	


	#endif
