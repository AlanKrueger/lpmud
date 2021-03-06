#include <sys/types.h>
#include <stdio.h>
#include "lint.h"

#ifdef malloc
#undef malloc
#undef free
#endif
/* #define DEBUGMALLOC */
int debugmalloc;
/*
 * This is a malloc optimized to use as little memory as possible.
 * It is presumed that more memory is allocated than released, and that
 * the free list will be small.
 *
 * Allocate at least 8 bytes, and all blocks on 4 byte alignments.
 */

#define CHUNK_SIZE	0x10000

static int limits[] = { 8, 12, 16, 20, 24, 28, 32, 40, 80, 300 };
#define SIZE_LIMITS (sizeof limits / sizeof limits[0])

struct free_l {
    int size;
    struct free_l *next;
};

/*
 * Reserv one big chunk of memory to use when sbrk() fails, so that
 * the game can be shut down in a pretty way.
 */
static char reserved_area_2[0x40000];
static char *reserved_area = reserved_area_2;

static struct free_l *free_list[SIZE_LIMITS + 1];
int stat_alloced_blocks[SIZE_LIMITS + 1];
int stat_alloced_data[SIZE_LIMITS + 1];

int malloc_total_alloced, malloc_total_free, malloc_free_blocks;

void slow_shut_down PROT((int));

void free(item_p)
    char *item_p;
{
    struct free_l *flp;
    int i;

    item_p -= sizeof flp->size;
    /* check_consistency(); */
    flp = (struct free_l *)item_p;
#ifdef DEBUGMALLOC
    if (debugmalloc)
	mdebug(0, &flp->next);
#endif
    for (i=0; i<SIZE_LIMITS; i++) {
	if (flp->size <= limits[i])
	    break;
    }
    flp->next = free_list[i];
    free_list[i] = flp;
    stat_alloced_blocks[i] -= 1;
    stat_alloced_data[i] -= flp->size;
    malloc_free_blocks += 1;
    malloc_total_free += flp->size;
    malloc_total_alloced -= flp->size;
    /* check_consistency(); */
}

/*
 * Return best fit !
 */
char *malloc(size)
    int size;
{
    struct free_l **flpp, *flp, **bestpp;
    int divergence, chunk_size, i;
    extern caddr_t sbrk();

    /* check_consistency(); */
    size = (size + 7) & ~3;
    bestpp = 0;
    divergence = 0x7ffffff;
    for (i=0; i<SIZE_LIMITS+1; i++) {
	if (i < SIZE_LIMITS && size > limits[i])
	    continue;
	for (flpp = &free_list[i]; *flpp; flpp = &(*flpp)->next) {
	    flp = *flpp;
	    if (flp->size == size || flp->size == size + 4) {
		*flpp = flp->next;
		malloc_total_alloced += flp->size;
		malloc_total_free -= flp->size;
		malloc_free_blocks -= 1;
		stat_alloced_blocks[i] += 1;
		stat_alloced_data[i] += flp->size;
		/* check_consistency(); */
#ifdef DEBUGMALLOC
		if (debugmalloc)
		    mdebug(1, &flp->next);
#endif
		return (char *)&flp->next;
	    }
	    if (flp->size > size && flp->size - size < divergence) {
		bestpp = flpp;
		divergence = flp->size - size;
	    }
	}
	if (bestpp)
	    break;
    }
    /*
     * If we found a good, but not perfect match, then split it up
     * in two parts. The left over part is put back into the lists with
     * free(), and the part with the correct size is returned.
     */
    if (bestpp) {
	struct free_l *new_flp;
	flp = *bestpp;
	new_flp = (struct free_l *)((char *)flp + size);
	new_flp->size = flp->size - size;
	*bestpp = flp->next;
	/*
	 * Some of the following gunk can be removed if the recursive call
	 * to free() is replaced by inline code.
	 */
	/* We need this loop to update statistics correctly. */
	for (i=0; i < SIZE_LIMITS; i++)
	    if (size <= limits[i])
		break;
	stat_alloced_blocks[i] += 1;
	stat_alloced_data[i] += size;
	/* We need this loop to update statistics correctly. */
	for (i=0; i < SIZE_LIMITS; i++)
	    if (new_flp->size <= limits[i])
		break;
	stat_alloced_blocks[i] += 1;
	stat_alloced_data[i] += new_flp->size;
	malloc_total_alloced += flp->size;
	malloc_total_free -= flp->size;
	malloc_free_blocks -= 1;
	free((char *)&new_flp->next);
	/* check_consistency(); */
	flp->size = size;
#ifdef DEBUGMALLOC
	if (debugmalloc)
	    mdebug(1, &flp->next);
#endif
	return (char *)&flp->next;
    }
    /*
     * No block found.
     * Get a new big chunk, and insert it last.
     * To insert it last is not important when using best fit,
     * but it will cost no more, and work if using first fit.
     */
    chunk_size = size > CHUNK_SIZE ? size : CHUNK_SIZE;
    flp = (struct free_l *)sbrk(chunk_size);
    if (flp == (struct free_l *)-1) {
	/* It feels sort of fun to use an area from the data space. */
	flp = (struct free_l *)reserved_area;
	reserved_area = 0;
	chunk_size = sizeof(reserved_area_2);
	if (size > chunk_size || flp == 0) {
	    fprintf(stderr, "Totally out of memory, last chunk: %d\n", size);
	    exit(1);
	}
    }
    flp->size = chunk_size;
    flp->next = 0;
    *(flpp) = flp;
    malloc_total_free += chunk_size;
    malloc_free_blocks += 1;
    if (reserved_area == 0) {
	/*
	 * The call of shutdown will call malloc() recursively,
	 * but this is no problem from here, as long as not too much
	 * data is used. If we really run out of memory, we have to take
	 * the game down immedialtely.
	 */
	slow_shut_down(6);	/* Give players 6 minutes to quit. */
	fprintf(stderr, "Game shutdown because out of memory.\n");
    }
    /*
     * Lazy here. The split could be done here, but as it is rather unusuall,
     * it won't cost much to call malloc() again.
     */
#ifdef DEBUGMALLOC
    {
	char *tmp = malloc(size-4);
	if (debugmalloc)
	    mdebug(1, tmp);
	return tmp;
    }
#else
    return malloc(size - 4);
#endif
}

char *realloc(p, size)
    char *p;
    int size;
{
    struct free_l *flp;
    char *p2;

    /* check_consistency(); */
    flp = (struct free_l *)(p - 4);
    if (flp->size >= size + 4)
	return p;
    p2 = malloc(size);
    if (p2 == 0)
	return 0;
    memcpy(p2, p, flp->size);
    free(p);
    return p2;
}

void dump_malloc_data() {
    int stat[SIZE_LIMITS + 1];
    int i;
    struct free_l *flp;

    for (i=0; i<SIZE_LIMITS+1; i++)
	stat[i] = 0;
    for (i=0; i<SIZE_LIMITS+1; i++) {
	for (flp = free_list[i]; flp; flp = flp->next) {
	    stat[i]++;
	}
    }
    add_message("malloc_total_free:    %d\n", malloc_total_free);
    add_message("malloc_total_alloced: %d\n", malloc_total_alloced);
    add_message("malloc_free_blocks:   %d\n", malloc_free_blocks);
    for (i=0; i<SIZE_LIMITS; i++)
	add_message("Size %3d: %5d, %5d: %6d\n", limits[i], stat[i],
		    stat_alloced_blocks[i], stat_alloced_data[i]);
    add_message("Size    : %5d, %5d: %6d\n", stat[SIZE_LIMITS],
		stat_alloced_blocks[i], stat_alloced_data[i]);
}

/*
find_alloced_data() {
    struct free_l *flp;

    for (flp = free_list; flp; flp = flp->next) {
	printf("0x%x: 0x%x\n", flp, flp->size);
    }
}
*/

/*
check_consistency() {
    register struct free_l *flp;
    int i;

    for (i=0, flp = free_list; flp; flp = flp->next, i++)
	if (i > malloc_free_blocks)
	    fatal("Bad free block list.\n");
    if (i != malloc_free_blocks)
	fatal("Bad free block list\n");
}
*/

/*
 * Insert a free block in a sorted list of free blocks.
 */
static void insert_block(flp, flpp)
    struct free_l *flp, **flpp;
{
    while(*flpp && *flpp < flp)
	flpp = &(*flpp)->next;
    flp->next = *flpp;
    *flpp = flp;
}

/*
 * Take a list of free blocks, and join adjacent blocks.
 */
void static recombine(flp)
    struct free_l *flp;
{
    while (flp) {
	while(flp->size + (char *)flp == (char *)flp->next) {
	    flp->size += flp->next->size;
	    flp->next = flp->next->next;
	}
	flp = flp->next;
    }
}

/*
 * Join all adjacent blocks in all free lists, and recreate
 * the free lists.
 */
int resort_free_list() {
    int i;
    struct free_l *flp, *all_blocks = 0, *flp_next, *flp_last;
    struct free_l *remember[SIZE_LIMITS+1];

    malloc_free_blocks = 0;
    for (i=0, flp_last = 0; i<SIZE_LIMITS+1; i++) {
	for (flp = free_list[i]; flp; flp = flp_next) {
	    flp_next = flp->next;
	    /* A small optimization here. */
	    if (flp_last && flp > flp_last)
		insert_block(flp, &flp_last);
	    else
		insert_block(flp, &all_blocks);
	    flp_last = flp;
	}
	free_list[i] = 0;
    }
    recombine(all_blocks);
    flp_next = all_blocks;
    for (i=0; i<SIZE_LIMITS+1; i++)
	remember[i] = 0;
    for (flp = flp_next; flp_next; flp = flp_next) {
	flp_next = flp->next;
	for (i=0; i<SIZE_LIMITS; i++)
	    if (flp->size <= limits[i])
		break;
	if (remember[i])
	    remember[i]->next = flp;
	else
	    free_list[i] = flp;
	remember[i] = flp;
	malloc_free_blocks++;
    }
    for (i=0; i<SIZE_LIMITS+1; i++) {
	if (remember[i])
	    remember[i]->next = 0;
    }
    return malloc_free_blocks;
}

#ifdef DEBUGMALLOC	
#define MAXL	10000

static buff[MAXL];
static compare_value;

mdebug(all, p)
    int all, p;
{
    int i;
    for (i=0; buff[i] != p && i < MAXL && (buff[i] || !all); i++)
	;
    if (p == compare_value)
	p = compare_value;
    if (all) {
	if (p == compare_value)
	    p = compare_value;
	if (i < MAXL) {
	    if (buff[i] == 0) {
		buff[i] = p;
		return;
	    }
	    abort();
	    fatal("Allocating used buffer.\n");
	}
	abort();
	fatal("Too small allocate buffer.\n");
    }
    if (p == compare_value)
	p = compare_value;
    if (i < MAXL) {
	buff[i] = 0;
	return;
    }
}

find_allocated() {
    int i;
    struct free_l *flp;

    for (i=0; i<MAXL; i++) {
	if (buff[i] == 0)
	    continue;
	flp = (struct free_l *)(buff[i] - 4);
	printf("0x%x: %d\n", flp->next, flp->size);
    }
}
#endif

/*
 * calloc() is provided because some stdio packages uses it.
 */
char *calloc(nelem, sizel)
    int nelem, sizel;
{
    char *p;

    if (nelem == 0 || sizel == 0)
	return 0;
    p = malloc(nelem * sizel);
    if (p == 0)
	return 0;
    (void)memset(p, '\0', nelem * sizel);
    return p;
}
