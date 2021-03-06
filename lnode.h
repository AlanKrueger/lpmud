#ifndef PROT
#define PROT(x) ()
#endif
/*
 * Define all nodes used by the interpreter.
 * It is extremly important that these nodes are as small as possible,
 * because they are the outstandingly most allocated data structure.
 *
 * Common for all nodes are:
 * type:	The type of the node.
 * line:	The line in the source. The 4 top bits store the
 *		basic type of the node (L_ something). Use L_MASK to mask
 *		out either the line number or basic type.
 */

#define L_SINGLE		0x1000
struct lnode_single {
    unsigned short type;
    unsigned short line;
};

#define L_NUMBER		0x2000
struct lnode_number {
    unsigned short type;
    unsigned short line;
    int number;
};

#define L_NAME			0x3000
struct lnode_name {
    unsigned short type;
    unsigned short line;
    char *name;
};

#define L_VARIABLE		0x4000
struct lnode_variable {
    unsigned short type;
    unsigned short line;
    int number;
};

#define L_1			0x5000
struct lnode_1 {
    unsigned short type;
    unsigned short line;
    struct lnode *expr;
};

#define L_2			0x6000
struct lnode_2 {
    unsigned short type;
    unsigned short line;
    struct lnode *expr1;
    struct lnode *expr2;
};

#define	L_3			0x7000
struct lnode_3 {
    unsigned short type;
    unsigned short line;
    struct lnode *expr1;
    struct lnode *expr2;
    struct lnode *expr3;
};

#define L_DEF			0x8000
struct lnode_def {
    unsigned short type;
    unsigned short line;
    char *name;
    struct lnode *block;
    struct lnode_def *next;
    unsigned char num_var;	/* Number of local variables + arguments */
    unsigned char num_arg;	/* Number of arguments. */
    unsigned short num_ref;
    short is_static;		/* Can not be called from outside. */
    short length;		/* String length of name. */
};

#define L_VAR_DEF		0x9000
struct lnode_var_def {
    unsigned short type;
    unsigned short line;
    char *name;
    struct lnode_var_def *next;
    short num_var;
    short num_arg;		/* This /ne is hardly used, is it ? */
    int is_static;
};

#define L_FUNCALL		0xa000
struct lnode_funcall {
    unsigned short type;
    unsigned short line;
    struct lnode *expr;
    char *name;
};

#define L_BLOCK			0xb000
struct lnode_block {
    unsigned short type;
    unsigned short line;
    int num_nodes;		/* Number of nodes in this block */
    char *block;
};

#define L_CONSTANT		0xc000	/* Used for non-allocateable lnodes */

#define L_MASK			0xf000
#define L_MAX			0xc000	/* Highest number */
#define L_SHIFT			12	/* Number of bits to shift */
struct lnode {
    unsigned short type;
    unsigned short line;
    struct lnode *a1, *a2, *a3;	/* Statements inside this statement */
};

struct lnode_var_def *find_status PROT((char *, int));

struct lnode_number *alloc_lnode_number PROT((int, int));
struct lnode_block *alloc_lnode_block PROT((struct lnode *));
struct lnode_name *alloc_lnode_name PROT((int, char *));
struct lnode_variable *alloc_lnode_variable PROT((int, int));
struct lnode_1 *alloc_lnode_1 PROT((int, struct lnode *));
struct lnode_2 *alloc_lnode_2 PROT((int, struct lnode *, struct lnode *));
struct lnode_3 *alloc_lnode_3 PROT((int, struct lnode *, struct lnode *,
				    struct lnode *));
struct lnode_def *alloc_lnode_def PROT((int, char *, struct lnode *, int));
struct lnode_funcall *alloc_lnode_funcall PROT((int, char *, struct lnode *));
struct lnode_single *alloc_lnode_single PROT((int));

extern struct lnode_var_def *prog_status;
void alloc_lnode_var_def PROT((int, char *, int));
int free_prog PROT((struct lnode_def *, char *, int));
void free_sub_part PROT((struct lnode *, int)),
    add_prog_ref PROT((struct lnode_def *)),
    free_lnode PROT((struct lnode *, int));

extern int lnode_size[];
