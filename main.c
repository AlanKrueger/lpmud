#include <stdio.h>
#include <string.h>
#include <math.h>
#include "lint.h"
#include "lnode.h"
#include "interpret.h"
#include "object.h"
#include "config.h"

struct value const0, const1;

extern struct lnode *prog;

extern int current_line;

int d_flag = 0;	/* Run with debug */
int t_flag = 0;	/* Disable heart beat and reset */
int e_flag = 0;	/* Load empty, without castles. */
#ifdef YYDEBUG
extern int yydebug;
#endif

int port_number = PORTNO;
char *reserved_area;	/* reserved for malloc() */

double consts[5];

int main(argc, argv)
    int argc;
    char **argv;
{
    char *p;
    extern int current_time;
    int i;

    if (argc == 2) {
	if (strcmp(argv[1], "-e") == 0)
	    e_flag++;
	else if (strcmp(argv[1], "-d") == 0)
	    d_flag++;
	else if (strcmp(argv[1], "-t") == 0)
	    t_flag++;
#ifdef YYDEBUG
	else if (strcmp(argv[1], "-y") == 0)
	    yydebug = 1;
#endif
	else port_number = atoi(argv[1]);
    }
#ifdef DRAND48
    srand48(time(0));
#else
#ifdef RANDOM
    srandom(time(0));
#else
    fprintf(stderr, "No random generator specified!\n");
#endif /* RANDOM */
#endif /* DRAND48 */
    current_time = time(0);
    if (RESERVED_SIZE > 0)
	reserved_area = malloc(RESERVED_SIZE);
    for (i=0; i < sizeof consts / sizeof consts[0]; i++)
	consts[i] = exp(- i / 900.0);
    init_string_space();
    chdir(MUD_LIB);
    init_constant_lnodes();
    compute_lnode_size();
    load_wiz_file();
    const0.type = T_NUMBER;
    const0.u.number = 0;
    const1.type = T_NUMBER;
    const1.u.number = 1;
    backend();
    return 0;
}

char *string_copy(str)
    char *str;
{
    char *p;

    p = xalloc(strlen(str)+1);
    (void)strcpy(p, str);
    return p;
}

/*VARARGS1*/
void debug_message(a, b, c, d, e, f, g, h, i, j)
    char *a;
    int b, c, d, e, f, g, h, i, j;
{
    static FILE *fp = NULL;
    char deb[100];
    char name[100];

    if (fp == NULL) {
	gethostname(name,sizeof name);
	sprintf(deb,"%s.debug.log",name);
	fp = fopen(deb, "w");
	if (fp == NULL) {
	    perror(deb);
	    abort();
	}
    }
    (void)fprintf(fp, a, b, c, d, e, f, g, h, i, j);
    (void)fflush(fp);
}

void debug_message_value(v)
    struct value *v;
{
    if (v == 0) {
	debug_message("<NULL>");
	return;
    }
    switch(v->type) {
    case T_NUMBER:
	debug_message("%d", v->u.number);
	return;
    case T_STRING:
	debug_message("\"%s\"", v->u.string);
	return;
    case T_OBJECT:
	debug_message("OBJ(%s)", v->u.ob->name);
	return;
    default:
	fatal("<INVALID>\n");
	return;
    }
}

#ifdef malloc
#undef malloc
#endif

int slow_shut_down_to_do = 0;

char *xalloc(size)
    int size;
{
    char *p;

    if (size == 0)
	fatal("Tried to allocate 0 bytes.\n");
    p = malloc(size);
    if (p == 0) {
	if (reserved_area) {
	    free(reserved_area);
	    p = "Temporary out of MEMORY. Freeing reserve.\n";
	    write(1, p, strlen(p));
	    reserved_area = 0;
	    slow_shut_down_to_do = 6;
	    return xalloc(size);	/* Try again */
	}
	p = "Totally out of MEMORY.\n";
	write(1, p, strlen(p));
	exit(2);
    }
    return p;
}
