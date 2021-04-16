
# line 2 "lang.y"
/*
 * This is the grammar definition of LPC. Expect one shift/reduce conflict,
 * because of if-then-else. The default, to shift this conflict, is the
 * correct solution.
 */
#include <string.h>
#include <stdio.h>
#include "lint.h"
#include "lnode.h"
#include "config.h"
#include "interpret.h"
#include "object.h"

#define YYMAXDEPTH	600

struct lnode *prog, *heart_beat;
int variable_count;
void yyerror(), free_all_local_names(), add_local_name(), smart_log();
extern int yylex(), check_deklared();
static void copy_variables();
int static_variable_flag;

char *argument_name;	/* The name of the current argument. */
char *xalloc(), *string_copy();

extern int current_line;
/*
 * 'inherit_file' is used as a flag. If it is set to a string
 * after yyparse(), this string should be loaded as an object,
 * and the original object must be loaded again.
 * 'inherit_ob' will point to the super class object. This value is saved
 * so that load_object() can set up pointers to it.
 */
extern char *current_file, *inherit_file;

extern struct object *find_object2();

struct object *inherit_ob;

char *local_names[MAX_LOCAL];
int current_number_of_locals = 0;
static int num_arg;
struct lnode_def *current_functions = 0;

# line 76 "lang.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif

{
	struct lnode *lnode;
	int number;
	char *string;
} YYSTYPE;
# define F_THIS_PLAYER 257
# define F_IF 258
# define F_IDENTIFIER 259
# define F_LAND 260
# define F_LOR 261
# define F_STATUS 262
# define F_SET_TRUE 263
# define F_SET_FALSE 264
# define F_CONS 265
# define F_RETURN 266
# define F_NOT 267
# define F_WRITE 268
# define F_STRING 269
# define F_ADD_VERB 270
# define F_ADD_ADJ 271
# define F_ADD_SUBST 272
# define F_ADD_ACTION 273
# define F_MOVE_OBJECT 274
# define F_INC 275
# define F_DEC 276
# define F_POST_INC 277
# define F_POST_DEC 278
# define F_COMMA 279
# define F_NUMBER 280
# define F_ASSIGN 281
# define F_INT 282
# define F_CALL_OTHER 283
# define F_ADD 284
# define F_SUBTRACT 285
# define F_MULTIPLY 286
# define F_DIVIDE 287
# define F_LT 288
# define F_GT 289
# define F_EQ 290
# define F_GE 291
# define F_LE 292
# define F_ARGUMENT 293
# define F_FUNCTION 294
# define F_CLONE_OBJECT 295
# define F_THIS_OBJECT 296
# define F_SAVE_OBJECT 297
# define F_RESTORE_OBJECT 298
# define F_NE 299
# define F_ENVIRONMENT 300
# define F_ADD_EQ 301
# define F_SUB_EQ 302
# define F_DIV_EQ 303
# define F_MULT_EQ 304
# define F_PRESENT 305
# define F_COMMAND 306
# define F_SET_LIGHT 307
# define F_DESTRUCT 308
# define F_CREATE_WIZARD 309
# define F_NEGATE 310
# define F_SAY 311
# define F_STRLEN 312
# define F_SUBSCRIPT 313
# define F_WHILE 314
# define F_BREAK 315
# define F_SHUTDOWN 316
# define F_LOG_FILE 317
# define F_DO 318
# define F_FOR 319
# define F_SSCANF 320
# define F_SHOUT 321
# define F_STRING_DECL 322
# define F_LOCAL_NAME 323
# define F_FIRST_INVENTORY 324
# define F_NEXT_INVENTORY 325
# define F_ENABLE_COMMANDS 326
# define F_RANDOM 327
# define F_INPUT_TO 328
# define F_CRYPT 329
# define F_LS 330
# define F_CAT 331
# define F_FIND_LIVING 332
# define F_TELL_OBJECT 333
# define F_PEOPLE 334
# define F_ED 335
# define F_LIVING 336
# define F_LOWER_CASE 337
# define F_ELSE 338
# define F_CAPITALIZE 339
# define F_SET_HEART_BEAT 340
# define F_SNOOP 341
# define F_TELL_ROOM 342
# define F_FIND_OBJECT 343
# define F_WIZLIST 344
# define F_RM 345
# define F_CONST0 346
# define F_CONST1 347
# define F_BLOCK 348
# define F_TRANSFER 349
# define F_REGCOMP 350
# define F_REGEXEC 351
# define F_LOCALCMD 352
# define F_SWAP 353
# define F_CONTINUE 354
# define F_ADD_WORTH 355
# define F_TIME 356
# define F_MOD 357
# define F_MOD_EQ 358
# define F_QUERY_IP_NUMBER 359
# define F_INHERIT 360
# define F_COLON_COLON 361
# define F_CREATOR 362
# define F_STATIC 363
# define F_CALL_OUT 364
# define F_REMOVE_CALL_OUT 365
# define F_COMBINE_FREE_LIST 366
# define F_ALLOCATE 367
# define F_SIZEOF 368
# define F_DISABLE_COMMANDS 369
# define F_CTIME 370
# define F_INTP 371
# define F_STRINGP 372
# define F_OBJECTP 373
# define F_POINTERP 374
# define F_USERS 375
# define F_ARROW 376
# define F_PREVIOUS_OBJECT 377
# define F_AGGREGATE 378
# define F_EXTRACT 379
# define F_FILE_NAME 380
# define F_QUERY_VERB 381
# define F_TAIL 382
# define F_QUERY_HOST_NAME 383
# define F_EXPLODE 384
# define F_COMPL 385
# define F_AND 386
# define F_AND_EQ 387
# define F_OR 388
# define F_OR_EQ 389
# define F_XOR 390
# define F_XOR_EQ 391
# define F_LSH 392
# define F_LSH_EQ 393
# define F_RSH 394
# define F_RSH_EQ 395
# define F_MKDIR 396
# define F_RMDIR 397
# define F_QUERY_SNOOP 398
# define F_FIND_PLAYER 399
# define F_WRITE_FILE 400
# define F_FILE_SIZE 401
# define F_PARSE_COMMAND 402
# define F_IMPLODE 403
# define F_QUERY_IDLE 404
# define F_QUERY_LOAD_AVERAGE 405
# define F_FILTER_OBJECTS 406
# define F_NOTIFY_FAIL 407
# define F_CATCH 408
# define F_THROW 409
# define F_SET_LIVING_NAME 410
# define F_SET_BIT 411
# define F_CLEAR_BIT 412
# define F_TEST_BIT 413
# define F_RUSAGE 414

/* #include <malloc.h> */
#include <memory.h>
#include <values.h>

#ifdef __cplusplus

#ifndef yyerror
	void yyerror(const char *);
#endif
#ifndef yylex
	int yylex(void);
#endif
	int yyparse(void);

#endif
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 477 "lang.y"


void yyerror(str)
char *str;
{
    extern int num_parse_error;

    if (num_parse_error > 5)
	return;
    (void)fprintf(stderr, "%s: %s line %d\n", current_file, str,
		  current_line);
    fflush(stderr);
    smart_log(current_file, current_line, str);
    if (num_parse_error == 0)
	save_error(str, current_file, current_line);
    num_parse_error++;
}

int check_declared(str)
    char *str;
{
    struct lnode_var_def *p;

    for (p = prog_status; p; p = p->next) {
	if (strcmp(p->name, str) == 0)
	    return p->num_var;
    }
    return -1;
}

int check_deklared(str)
    char *str;
{
    char buff[100];
    int r;

    r = check_declared(str);
    if (r < 0) {
        (void)sprintf(buff, "Variable %s not declared !", str);
        yyerror(buff);
    }
    return r;
}

void free_all_local_names()
{
    int i;

    for (i=0; i<current_number_of_locals; i++) {
	free(local_names[i]);
	local_names[i] = 0;
    }
    current_number_of_locals = 0;
}

void add_local_name(str)
    char *str;
{
    if (current_number_of_locals == MAX_LOCAL)
	yyerror("Too many local variables\n");
    else
	local_names[current_number_of_locals++] = str;
}

int num_val(p)
    struct lnode_number *p;
{
    switch(p->type) {
    case F_NUMBER:
        return p->number;
    case F_CONST0:
	return 0;
    case F_CONST1:
	return 1;
    default:
	fatal("Illegal type of number.\n");
    }
    /*NOTREACHED*/
}

/*
 * It could be possible to do '#include "/etc/passwd"' in the definition
 * of an object. The compilation would fail, but the .i file would remain
 * with interesting data.
 * Prevent this by checking the name of teh include file.
 */

int illegal_include_file(str)
    char *str;
{
    char *p;
    int i;

    if (str[0] == '/')
	return 1;
    if (strlen(str) < 3)
	return 0;
    for (p = str + 3, i = 0; *p; p++)
	if (p[0] == '/' &&  p[-1] == '.' && p[-2] == '.' && p[-3] == '/')
	    i += 1;
    if (i > 3)
	return 1;
    return 0;
}

static void copy_one_variable(p)
    struct lnode_var_def *p;
{
    if (p->next)
	copy_one_variable(p->next);
    static_variable_flag = p->is_static;
    alloc_lnode_var_def(F_STATUS, string_copy(p->name), variable_count++);
}

static void copy_variables(from)
    struct object *from;
{
    if (variable_count > 0)
	yyerror("Illegal to declare variables before the inherit statement");
    if (!from->status)
	return;
    copy_one_variable(from->status);
}

int defined_function(s)
    char *s;
{
    struct lnode_def *p;

    for(p = current_functions; p; p = p->next) {
        if (strcmp(p->name, s) == 0)
	    return 1;
    }
    return 0;
}
yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 3,
	0, 2,
	-2, 17,
-1, 39,
	125, 37,
	-2, 0,
-1, 42,
	125, 37,
	-2, 0,
-1, 58,
	59, 70,
	-2, 0,
-1, 62,
	40, 125,
	-2, 118,
-1, 117,
	59, 52,
	-2, 0,
-1, 128,
	125, 72,
	-2, 0,
-1, 130,
	41, 72,
	-2, 0,
-1, 146,
	376, 113,
	91, 113,
	-2, 104,
-1, 148,
	376, 113,
	91, 113,
	-2, 105,
-1, 190,
	59, 52,
	-2, 0,
-1, 192,
	41, 72,
	-2, 0,
-1, 194,
	41, 72,
	125, 72,
	-2, 0,
-1, 205,
	41, 52,
	-2, 0,
	};
# define YYNPROD 129
# define YYLAST 699
yytabelem yyact[]={

    96,   123,   139,    94,   140,    96,     8,   165,   203,     7,
    96,    22,    16,   158,   120,   121,    13,   126,   122,   132,
    35,    33,    11,    42,   137,   109,   135,   159,    83,    61,
   193,    91,    17,    44,    72,    38,   129,    59,   191,    65,
    95,    82,   169,    53,    30,    23,   110,   205,   190,   108,
   107,    31,    19,    60,    10,   144,   141,    40,   142,   110,
   143,   194,   210,   112,    32,   145,    30,    28,    21,   206,
   204,   201,    18,   195,   188,    24,    84,   187,   111,   168,
   115,    29,   192,   189,   130,   117,   114,   113,    14,    15,
   131,    25,   118,    50,    39,    27,    26,    12,    34,    20,
    93,   119,     6,     9,   127,     2,     1,     5,    69,    78,
    92,    77,    71,    66,    48,    47,    46,    79,   153,    80,
    68,    85,    49,     4,    36,     3,   147,   147,    37,    41,
    67,    45,    81,    70,     0,     0,     0,     0,    90,   154,
   146,   148,   150,   150,   150,    70,   155,   156,   157,     0,
    90,   160,     0,   125,     0,   166,     0,   163,     0,   164,
   162,     0,     0,   161,     0,   149,   151,   152,     0,     0,
   182,   183,   170,   172,   170,     0,   150,    70,     0,   150,
   150,   180,   181,   150,     0,   150,     0,   150,   150,   150,
   150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     0,     0,    70,     0,     0,     0,     0,    90,     0,     0,
     0,   196,   197,     0,   120,   121,    38,     0,   199,    89,
   184,   185,   186,   198,   160,     0,     0,   207,    38,     0,
   208,    89,     0,   209,   211,   200,   170,   202,   170,   160,
   102,   103,   106,   104,     0,   102,   103,   106,   104,     0,
   102,   103,   106,   104,   133,   136,   138,     0,     0,   167,
    70,     0,   171,   134,   173,    90,   174,   175,   176,   177,
   178,   179,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   128,   124,     0,    89,     0,
     0,     0,     0,     0,     0,     0,     0,   105,     0,     0,
     0,    70,   105,     0,     0,     0,    90,   105,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    97,     0,    98,     0,
    99,    97,   100,    98,   101,    99,    97,   100,    98,   101,
    99,     0,   100,    38,   101,     0,    89,     0,     0,    43,
     0,    54,    62,     0,     0,    16,   139,     0,   140,    58,
    88,   116,    73,    54,    62,     0,     0,     0,    86,    87,
     0,    58,    88,    74,    73,    17,     0,    70,     0,     0,
    86,    87,    90,     0,     0,    74,    63,    89,     0,     0,
     0,     0,     0,     0,     0,     0,    62,     0,    63,     0,
     0,     0,     0,     0,     0,     0,    73,    55,    51,     0,
     0,    56,    57,     0,     0,    18,    64,    74,   116,    55,
    51,    62,     0,    56,    57,     0,     0,     0,    64,    88,
    63,    73,     0,     0,     0,     0,     0,    86,    87,    75,
    76,     0,    74,     0,     0,     0,     0,    52,     0,     0,
     0,    75,    76,     0,    78,    63,     0,     0,     0,    52,
    64,     0,     0,    89,     0,     0,    78,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    43,     0,    54,    62,
     0,     0,     0,    75,    76,    64,    58,    88,     0,    73,
     0,     0,     0,     0,     0,    86,    87,     0,    78,     0,
    74,     0,     0,     0,     0,     0,     0,     0,    75,    76,
     0,     0,     0,    63,     0,     0,     0,   116,     0,     0,
    62,     0,     0,    78,     0,     0,     0,     0,    88,     0,
    73,     0,     0,     0,    55,    51,    86,    87,    56,    57,
     0,    74,     0,    64,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    75,    76,     0,     0,
     0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
     0,    78,     0,     0,    64,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    62,     0,     0,     0,
     0,     0,     0,     0,    88,     0,    73,    75,    76,     0,
     0,     0,    86,    87,     0,     0,     0,    74,     0,     0,
     0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
    63,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    64,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    75,    76,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    78 };
yytabelem yypact[]={

-10000000,-10000000,-10000000,  -354,    -5,  -237,-10000000,-10000000,  -253,-10000000,
-10000000,    48,  -250,    -7,  -248,    25,-10000000,-10000000,-10000000,-10000000,
    40,    22,-10000000,-10000000,-10000000,    -8,    20,  -238,-10000000,-10000000,
  -239,-10000000,    25,-10000000,   -88,-10000000,-10000000,-10000000,-10000000,    93,
   -94,  -248,   220,   -56,    -9,-10000000,-10000000,-10000000,-10000000,   -10,
-10000000,   -13,   -13,    19,    47,    46,   105,    45,   261,-10000000,
   -61,  -243,-10000000,-10000000,-10000000,   -90,  -107,-10000000,-10000000,-10000000,
   162,   -58,    44,-10000000,-10000000,-10000000,-10000000,    52,  -240,-10000000,
-10000000,   -36,    13,    18,-10000000,-10000000,   137,   137,   337,   337,
   337,-10000000,     0,-10000000,-10000000,   261,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,   261,   261,   261,  -301,   -51,   261,-10000000,   261,
-10000000,-10000000,   337,   261,  -252,   337,   337,    38,   261,   337,
   261,   337,-10000000,   337,   337,   337,   337,   337,   337,   337,
   337,   337,   337,   337,   337,   337,-10000000,   -90,-10000000,-10000000,
  -261,-10000000,-10000000,-10000000,-10000000,-10000000,    36,    33,    43,   -11,
-10000000,-10000000,-10000000,   -55,    42,-10000000,-10000000,  -390,-10000000,   -95,
    17,  -390,    32,  -390,  -390,  -390,  -390,  -390,  -390,  -390,
    13,    13,    18,    18,-10000000,-10000000,-10000000,   105,   105,   261,
   261,-10000000,   261,    30,   261,-10000000,  -330,-10000000,    29,   -12,
    28,-10000000,-10000000,   105,   -13,   261,-10000000,-10000000,-10000000,    21,
   105,-10000000 };
yytabelem yypgo[]={

     0,   131,    37,    42,    29,    76,   130,    53,    57,    23,
   125,   123,   122,    39,   121,   120,    43,    41,    28,   119,
   117,   116,   115,   114,   132,   113,   112,   111,    33,    27,
    93,   108,    40,   107,    34,   106,   105,   103,   102,    99,
    98,    97,    89,    91,    25,    68,    96,    95,    94 };
yytabelem yyr1[]={

     0,    36,    35,    10,    10,    37,    37,    38,    31,    31,
    31,    40,    11,    41,    11,    11,    33,    33,    44,    44,
    39,    39,    42,    42,    42,    43,    43,    46,    47,    47,
    30,    48,    48,    45,    45,    45,    45,     8,     8,     8,
     9,     9,     9,     9,     9,     9,     9,     9,     9,    21,
    22,    23,    29,    29,    28,    28,    16,    16,    16,    32,
    32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
    12,    12,     3,     3,     3,     2,     2,     4,     4,    25,
    25,    26,    26,    27,    27,    20,    20,    20,    19,    19,
    19,    19,    19,    24,    24,    24,    17,    17,    17,    18,
    18,    18,    18,     5,     5,     5,     5,     5,     5,    14,
    14,    14,    13,    13,    13,    13,    13,    13,     7,     7,
     7,     7,    15,     6,     6,    34,    34,     1,     1 };
yytabelem yyr2[]={

     0,     1,     5,     7,     1,     0,     3,     7,     2,     2,
     2,     1,    15,     1,    11,     3,     3,     1,     2,     1,
     0,     2,     2,     2,     2,     2,     6,     5,     2,     0,
     9,     0,     8,     3,     7,     3,     3,     1,     5,     5,
     5,     2,     2,     2,     2,     5,     2,     5,     5,    11,
    15,    19,     1,     3,     3,     7,     2,     7,     7,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     5,     1,     3,     7,     2,     7,     2,     7,     2,
     7,     2,     7,     2,     7,     2,     7,     7,     2,     7,
     7,     7,     7,     2,     7,     7,     2,     7,     7,     2,
     7,     7,     7,     2,     5,     5,     5,     5,     5,     2,
     5,     5,     2,     2,     2,     2,     7,    11,     3,     3,
     2,     9,     3,     9,    13,     2,     5,    11,    15 };
yytabelem yychk[]={

-10000000,   -35,   -36,   -10,   -11,   -33,   -38,   363,   360,   -37,
    59,   259,   -41,   269,    40,   -42,   262,   282,   322,    59,
   -39,   -45,   259,   293,   323,   -43,   -46,   -47,    42,    41,
    44,    59,    44,   259,   -40,   259,   -43,   -30,   123,   -48,
    -8,   -42,    -9,   256,   -28,    -1,   -21,   -22,   -23,   -12,
   -30,   315,   354,   -16,   258,   314,   318,   319,   266,    -2,
    -7,    -4,   259,   293,   323,   -13,   -25,    -6,   -15,   -31,
    40,   -26,   -34,   269,   280,   346,   347,   -27,   361,   -20,
   -19,   -24,   -17,   -18,    -5,   -14,   275,   276,   267,   126,
    45,   125,   -45,    -8,    59,   -32,    61,   387,   389,   391,
   393,   395,   301,   302,   304,   358,   303,    59,    59,   -44,
    59,   -44,    44,    40,    40,    -9,   256,    40,   -28,   -32,
   275,   276,   261,    91,   376,   260,   124,   -28,   123,    94,
    40,    38,   259,   290,   299,    62,   291,    60,   292,   392,
   394,    43,    45,    42,    37,    47,    -7,   -13,    -7,    -5,
    -7,    -5,    -5,   -44,   -16,   -28,   -28,   -28,   314,   -29,
   -28,   -16,    -2,   -28,   -34,   259,    -4,   -24,    41,    -3,
   -16,   -24,    -3,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
   -17,   -17,   -18,   -18,    -5,    -5,    -5,    41,    41,    40,
    59,    93,    40,   125,    44,    41,    -9,    -9,   -28,   -29,
    -3,    41,    -3,   338,    41,    59,    41,    -9,   -44,   -29,
    41,    -9 };
yytabelem yydef[]={

     1,    -2,     4,    -2,     5,    13,    15,    16,     0,     3,
     6,     0,     0,     0,    20,    29,    22,    23,    24,     7,
     0,    21,    33,    35,    36,     0,    25,     0,    28,    11,
     0,    14,    29,    27,     0,    34,    26,    12,    31,    -2,
     0,     0,    -2,     0,     0,    41,    42,    43,    44,     0,
    46,    19,    19,    54,     0,     0,     0,     0,    -2,    56,
   113,    75,    -2,   119,   120,   109,    77,   112,   114,   115,
     0,    79,     0,   122,     8,     9,    10,    81,     0,    83,
    85,    88,    93,    96,    99,   103,     0,     0,     0,     0,
     0,    30,    19,    38,    39,     0,    59,    60,    61,    62,
    63,    64,    65,    66,    67,    68,    69,    40,    45,    47,
    18,    48,     0,     0,     0,     0,     0,    -2,    71,     0,
   110,   111,     0,     0,     0,     0,     0,     0,    -2,     0,
    -2,     0,   126,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    -2,     0,    -2,   106,
   113,   107,   108,    32,    58,    55,     0,     0,     0,     0,
    53,    57,    76,     0,     0,   125,    78,    80,   116,     0,
    73,    82,     0,    84,    86,    87,    89,    90,    91,    92,
    94,    95,    97,    98,   100,   101,   102,     0,     0,     0,
    -2,   121,    -2,     0,    -2,   123,   127,    49,     0,     0,
     0,   117,    74,     0,    19,    -2,   124,   128,    50,     0,
     0,    51 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{ char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"F_THIS_PLAYER",	257,
	"F_IF",	258,
	"F_IDENTIFIER",	259,
	"F_LAND",	260,
	"F_LOR",	261,
	"F_STATUS",	262,
	"F_SET_TRUE",	263,
	"F_SET_FALSE",	264,
	"F_CONS",	265,
	"F_RETURN",	266,
	"F_NOT",	267,
	"F_WRITE",	268,
	"F_STRING",	269,
	"F_ADD_VERB",	270,
	"F_ADD_ADJ",	271,
	"F_ADD_SUBST",	272,
	"F_ADD_ACTION",	273,
	"F_MOVE_OBJECT",	274,
	"F_INC",	275,
	"F_DEC",	276,
	"F_POST_INC",	277,
	"F_POST_DEC",	278,
	"F_COMMA",	279,
	"F_NUMBER",	280,
	"F_ASSIGN",	281,
	"F_INT",	282,
	"F_CALL_OTHER",	283,
	"F_ADD",	284,
	"F_SUBTRACT",	285,
	"F_MULTIPLY",	286,
	"F_DIVIDE",	287,
	"F_LT",	288,
	"F_GT",	289,
	"F_EQ",	290,
	"F_GE",	291,
	"F_LE",	292,
	"F_ARGUMENT",	293,
	"F_FUNCTION",	294,
	"F_CLONE_OBJECT",	295,
	"F_THIS_OBJECT",	296,
	"F_SAVE_OBJECT",	297,
	"F_RESTORE_OBJECT",	298,
	"F_NE",	299,
	"F_ENVIRONMENT",	300,
	"F_ADD_EQ",	301,
	"F_SUB_EQ",	302,
	"F_DIV_EQ",	303,
	"F_MULT_EQ",	304,
	"F_PRESENT",	305,
	"F_COMMAND",	306,
	"F_SET_LIGHT",	307,
	"F_DESTRUCT",	308,
	"F_CREATE_WIZARD",	309,
	"F_NEGATE",	310,
	"F_SAY",	311,
	"F_STRLEN",	312,
	"F_SUBSCRIPT",	313,
	"F_WHILE",	314,
	"F_BREAK",	315,
	"F_SHUTDOWN",	316,
	"F_LOG_FILE",	317,
	"F_DO",	318,
	"F_FOR",	319,
	"F_SSCANF",	320,
	"F_SHOUT",	321,
	"F_STRING_DECL",	322,
	"F_LOCAL_NAME",	323,
	"F_FIRST_INVENTORY",	324,
	"F_NEXT_INVENTORY",	325,
	"F_ENABLE_COMMANDS",	326,
	"F_RANDOM",	327,
	"F_INPUT_TO",	328,
	"F_CRYPT",	329,
	"F_LS",	330,
	"F_CAT",	331,
	"F_FIND_LIVING",	332,
	"F_TELL_OBJECT",	333,
	"F_PEOPLE",	334,
	"F_ED",	335,
	"F_LIVING",	336,
	"F_LOWER_CASE",	337,
	"F_ELSE",	338,
	"F_CAPITALIZE",	339,
	"F_SET_HEART_BEAT",	340,
	"F_SNOOP",	341,
	"F_TELL_ROOM",	342,
	"F_FIND_OBJECT",	343,
	"F_WIZLIST",	344,
	"F_RM",	345,
	"F_CONST0",	346,
	"F_CONST1",	347,
	"F_BLOCK",	348,
	"F_TRANSFER",	349,
	"F_REGCOMP",	350,
	"F_REGEXEC",	351,
	"F_LOCALCMD",	352,
	"F_SWAP",	353,
	"F_CONTINUE",	354,
	"F_ADD_WORTH",	355,
	"F_TIME",	356,
	"F_MOD",	357,
	"F_MOD_EQ",	358,
	"F_QUERY_IP_NUMBER",	359,
	"F_INHERIT",	360,
	"F_COLON_COLON",	361,
	"F_CREATOR",	362,
	"F_STATIC",	363,
	"F_CALL_OUT",	364,
	"F_REMOVE_CALL_OUT",	365,
	"F_COMBINE_FREE_LIST",	366,
	"F_ALLOCATE",	367,
	"F_SIZEOF",	368,
	"F_DISABLE_COMMANDS",	369,
	"F_CTIME",	370,
	"F_INTP",	371,
	"F_STRINGP",	372,
	"F_OBJECTP",	373,
	"F_POINTERP",	374,
	"F_USERS",	375,
	"F_ARROW",	376,
	"F_PREVIOUS_OBJECT",	377,
	"F_AGGREGATE",	378,
	"F_EXTRACT",	379,
	"F_FILE_NAME",	380,
	"F_QUERY_VERB",	381,
	"F_TAIL",	382,
	"F_QUERY_HOST_NAME",	383,
	"F_EXPLODE",	384,
	"F_COMPL",	385,
	"F_AND",	386,
	"F_AND_EQ",	387,
	"F_OR",	388,
	"F_OR_EQ",	389,
	"F_XOR",	390,
	"F_XOR_EQ",	391,
	"F_LSH",	392,
	"F_LSH_EQ",	393,
	"F_RSH",	394,
	"F_RSH_EQ",	395,
	"F_MKDIR",	396,
	"F_RMDIR",	397,
	"F_QUERY_SNOOP",	398,
	"F_FIND_PLAYER",	399,
	"F_WRITE_FILE",	400,
	"F_FILE_SIZE",	401,
	"F_PARSE_COMMAND",	402,
	"F_IMPLODE",	403,
	"F_QUERY_IDLE",	404,
	"F_QUERY_LOAD_AVERAGE",	405,
	"F_FILTER_OBJECTS",	406,
	"F_NOTIFY_FAIL",	407,
	"F_CATCH",	408,
	"F_THROW",	409,
	"F_SET_LIVING_NAME",	410,
	"F_SET_BIT",	411,
	"F_CLEAR_BIT",	412,
	"F_TEST_BIT",	413,
	"F_RUSAGE",	414,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"all : /* empty */",
	"all : program",
	"program : program def possible_semi_colon",
	"program : /* empty */",
	"possible_semi_colon : /* empty */",
	"possible_semi_colon : ';'",
	"inheritance : F_INHERIT F_STRING ';'",
	"number : F_NUMBER",
	"number : F_CONST0",
	"number : F_CONST1",
	"def : static F_IDENTIFIER '(' argument ')'",
	"def : static F_IDENTIFIER '(' argument ')' block",
	"def : static",
	"def : static type name_list ';'",
	"def : inheritance",
	"static : F_STATIC",
	"static : /* empty */",
	"req_semi : ';'",
	"req_semi : /* empty */",
	"argument : /* empty */",
	"argument : local_list",
	"type : F_STATUS",
	"type : F_INT",
	"type : F_STRING_DECL",
	"name_list : new_name",
	"name_list : new_name ',' name_list",
	"new_name : optional_star F_IDENTIFIER",
	"optional_star : '*'",
	"optional_star : /* empty */",
	"block : '{' local_declarations statements '}'",
	"local_declarations : /* empty */",
	"local_declarations : local_declarations type local_list req_semi",
	"local_list : F_IDENTIFIER",
	"local_list : local_list ',' F_IDENTIFIER",
	"local_list : F_ARGUMENT",
	"local_list : F_LOCAL_NAME",
	"statements : /* empty */",
	"statements : statement statements",
	"statements : error ';'",
	"statement : comma_expr ';'",
	"statement : cond",
	"statement : while",
	"statement : do",
	"statement : for",
	"statement : return ';'",
	"statement : block",
	"statement : F_BREAK req_semi",
	"statement : F_CONTINUE req_semi",
	"while : F_WHILE '(' comma_expr ')' statement",
	"do : F_DO statement F_WHILE '(' comma_expr ')' req_semi",
	"for : F_FOR '(' for_expr ';' for_expr ';' for_expr ')' statement",
	"for_expr : /* empty */",
	"for_expr : comma_expr",
	"comma_expr : expr0",
	"comma_expr : expr0 ',' comma_expr",
	"expr0 : expr1",
	"expr0 : variable assign expr0",
	"expr0 : error assign expr0",
	"assign : '='",
	"assign : F_AND_EQ",
	"assign : F_OR_EQ",
	"assign : F_XOR_EQ",
	"assign : F_LSH_EQ",
	"assign : F_RSH_EQ",
	"assign : F_ADD_EQ",
	"assign : F_SUB_EQ",
	"assign : F_MULT_EQ",
	"assign : F_MOD_EQ",
	"assign : F_DIV_EQ",
	"return : F_RETURN",
	"return : F_RETURN comma_expr",
	"expr_list : /* empty */",
	"expr_list : expr0",
	"expr_list : expr0 ',' expr_list",
	"expr1 : expr2",
	"expr1 : expr2 F_LOR expr1",
	"expr2 : expr211",
	"expr2 : expr211 F_LAND expr2",
	"expr211 : expr212",
	"expr211 : expr211 '|' expr24",
	"expr212 : expr213",
	"expr212 : expr212 '^' expr24",
	"expr213 : expr22",
	"expr213 : expr213 '&' expr24",
	"expr22 : expr23",
	"expr22 : expr24 F_EQ expr24",
	"expr22 : expr24 F_NE expr24",
	"expr23 : expr24",
	"expr23 : expr24 '>' expr24",
	"expr23 : expr24 F_GE expr24",
	"expr23 : expr24 '<' expr24",
	"expr23 : expr24 F_LE expr24",
	"expr24 : expr25",
	"expr24 : expr24 F_LSH expr25",
	"expr24 : expr24 F_RSH expr25",
	"expr25 : expr27",
	"expr25 : expr25 '+' expr27",
	"expr25 : expr25 '-' expr27",
	"expr27 : expr3",
	"expr27 : expr27 '*' expr3",
	"expr27 : expr27 '%' expr3",
	"expr27 : expr27 '/' expr3",
	"expr3 : expr31",
	"expr3 : F_INC variable",
	"expr3 : F_DEC variable",
	"expr3 : F_NOT expr3",
	"expr3 : '~' expr3",
	"expr3 : '-' expr3",
	"expr31 : expr4",
	"expr31 : variable F_INC",
	"expr31 : variable F_DEC",
	"expr4 : function_call",
	"expr4 : variable",
	"expr4 : string",
	"expr4 : number",
	"expr4 : '(' comma_expr ')'",
	"expr4 : '(' '{' expr_list '}' ')'",
	"variable : F_IDENTIFIER",
	"variable : F_ARGUMENT",
	"variable : F_LOCAL_NAME",
	"variable : expr4 '[' comma_expr ']'",
	"string : F_STRING",
	"function_call : function_name '(' expr_list ')'",
	"function_call : expr4 F_ARROW function_name '(' expr_list ')'",
	"function_name : F_IDENTIFIER",
	"function_name : F_COLON_COLON F_IDENTIFIER",
	"cond : F_IF '(' comma_expr ')' statement",
	"cond : F_IF '(' comma_expr ')' statement F_ELSE statement",
};
#endif /* YYDEBUG */
#ident	"@(#)yacc:yaccpar	1.17"

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, yynewmax * sizeof(type))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
			yyerror("yacc initialization error");
			YYABORT;
		}
	}
#endif

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			int yynewmax, yys_off, yyv_off;
			int *yys_base = yys;
			YYSTYPE *yyv_base = yyv;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				char *newyys = YYNEW(int);
				char *newyyv = YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
				yyerror( "yacc stack overflow" );
				YYABORT;
			}
			yymaxdepth = yynewmax;

			/* reset pointers into yys */
			yys_off = yys - yys_base;
			yy_ps = yy_ps + yys_off;
			yyps = yyps + yys_off;

			/* reset pointers into yyv */
			yyv_off = yyv - yyv_base;
			yypvt = yypvt + yyv_off;
			yy_pv = yy_pv + yyv_off;
			yypv = yypv + yyv_off;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
				/* FALLTHRU */
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 96 "lang.y"
{ current_functions = 0; } break;
case 2:
# line 96 "lang.y"
{ prog = yypvt[-0].lnode; } break;
case 3:
# line 99 "lang.y"
{ if (yypvt[-1].lnode != 0) {
	    struct lnode_def *p = (struct lnode_def *)yypvt[-1].lnode;
	    p->next = (struct lnode_def *)yypvt[-2].lnode;
	    yyval.lnode = (struct lnode *)p;
#if 0
	    if (defined_function(p->name))
	      yyerror("Illegal to redeclare function.");
#endif
	    current_functions = p;
	  } else
	    yyval.lnode = yypvt[-2].lnode;
        } break;
case 4:
# line 111 "lang.y"
{ yyval.lnode = 0; } break;
case 6:
# line 114 "lang.y"
{ yyerror("Extra ';'. Ignored."); } break;
case 7:
# line 117 "lang.y"
{
		    if (inherit_ob || inherit_file) {
			yyerror("Multiple inheritance not allowed.\n");
			free(yypvt[-1].string);
		    } else if (prog) {
			yyerror("inherit must come first.\n");
			free(yypvt[-1].string);
		    } else {
			inherit_ob = find_object2(yypvt[-1].string);
			if (inherit_ob == 0) {
			    inherit_file = yypvt[-1].string;
			    return 0;
			}
			free(yypvt[-1].string);
			copy_variables(inherit_ob);
		    }
		} break;
case 11:
# line 138 "lang.y"
{ num_arg = current_number_of_locals; } break;
case 12:
# line 140 "lang.y"
{ struct lnode_def *p;
	  p = alloc_lnode_def(F_IDENTIFIER,yypvt[-5].string,yypvt[-0].lnode,
			      current_number_of_locals);
	  p->num_arg = num_arg;
	  if (yypvt[-6].number)
	      p->is_static = 1;
	  yyval.lnode = (struct lnode *)p;
	  if (strcmp(p->name, "heart_beat") == 0) heart_beat = yyval.lnode;
	  if (argument_name) free(argument_name);
	  argument_name = 0; free_all_local_names(); } break;
case 13:
# line 152 "lang.y"
{ static_variable_flag = yypvt[-0].number; } break;
case 14:
# line 153 "lang.y"
{ yyval.lnode = 0; static_variable_flag = 0; } break;
case 15:
# line 154 "lang.y"
{ yyval.lnode = 0; } break;
case 16:
# line 156 "lang.y"
{ yyval.number = 1; } break;
case 17:
# line 157 "lang.y"
{ yyval.number = 0; } break;
case 19:
# line 161 "lang.y"
{ yyerror("Missing ';'"); } break;
case 27:
# line 172 "lang.y"
{ alloc_lnode_var_def(F_STATUS, yypvt[-0].string, variable_count++); } break;
case 30:
# line 177 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_block(yypvt[-1].lnode); } break;
case 33:
# line 182 "lang.y"
{ add_local_name(yypvt[-0].string); } break;
case 34:
# line 183 "lang.y"
{ add_local_name(yypvt[-0].string); } break;
case 35:
# line 184 "lang.y"
{ yyerror("Illegal to redeclare argument"); } break;
case 36:
# line 185 "lang.y"
{ yyerror("Illegal to redeclare local name"); } break;
case 37:
# line 187 "lang.y"
{ yyval.lnode = 0; } break;
case 38:
# line 189 "lang.y"
{ if (yypvt[-1].lnode == 0)
		      yyval.lnode = yypvt[-0].lnode;
		  else
		      yyval.lnode = (struct lnode *)alloc_lnode_2(F_CONS, yypvt[-1].lnode, yypvt[-0].lnode);
	        } break;
case 39:
# line 194 "lang.y"
{ yyval.lnode = 0; } break;
case 40:
# line 196 "lang.y"
{ yyval.lnode = yypvt[-1].lnode; } break;
case 45:
# line 197 "lang.y"
{ yyval.lnode = yypvt[-1].lnode; } break;
case 47:
# line 199 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_single(F_BREAK);
			    } break;
case 48:
# line 201 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_single(F_CONTINUE);
			    } break;
case 49:
# line 205 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_WHILE, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 50:
# line 208 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_DO, yypvt[-5].lnode, yypvt[-2].lnode); } break;
case 51:
# line 211 "lang.y"
{ yyval.lnode = (struct lnode *)
           alloc_lnode_2(F_CONS,yypvt[-6].lnode,
			 (struct lnode *)
			 alloc_lnode_2(F_CONS,
				       (struct lnode *)alloc_lnode_3(F_FOR,yypvt[-4].lnode,
								     yypvt[-2].lnode,yypvt[-0].lnode),
				       (struct lnode *)0)); } break;
case 52:
# line 220 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_single(F_CONST1); } break;
case 53:
# line 222 "lang.y"
{ yyval.lnode=yypvt[-0].lnode; } break;
case 54:
# line 225 "lang.y"
{ yyval.lnode=yypvt[-0].lnode; } break;
case 55:
# line 227 "lang.y"
{ 
	  if(yypvt[-0].lnode->type==F_COMMA)
	    yyval.lnode = (struct lnode *)alloc_lnode_2(F_COMMA, yypvt[-2].lnode, yypvt[-0].lnode);
	  else
	    yyval.lnode = (struct lnode *)alloc_lnode_2(F_COMMA, yypvt[-2].lnode,
			      (struct lnode *)alloc_lnode_2(F_COMMA, yypvt[-0].lnode, 0));
	} break;
case 57:
# line 237 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(yypvt[-1].number, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 58:
# line 238 "lang.y"
{ yyerror("Illegal LHS"); yyval.lnode = 0; } break;
case 59:
# line 240 "lang.y"
{ yyval.number = F_ASSIGN; } break;
case 60:
# line 241 "lang.y"
{ yyval.number = F_AND_EQ; } break;
case 61:
# line 242 "lang.y"
{ yyval.number = F_OR_EQ; } break;
case 62:
# line 243 "lang.y"
{ yyval.number = F_XOR_EQ; } break;
case 63:
# line 244 "lang.y"
{ yyval.number = F_LSH_EQ; } break;
case 64:
# line 245 "lang.y"
{ yyval.number = F_RSH_EQ; } break;
case 65:
# line 246 "lang.y"
{ yyval.number = F_ADD_EQ; } break;
case 66:
# line 247 "lang.y"
{ yyval.number = F_SUB_EQ; } break;
case 67:
# line 248 "lang.y"
{ yyval.number = F_MULT_EQ; } break;
case 68:
# line 249 "lang.y"
{ yyval.number = F_MOD; } break;
case 69:
# line 250 "lang.y"
{ yyval.number = F_DIV_EQ; } break;
case 70:
# line 252 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_RETURN, 0); } break;
case 71:
# line 253 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_RETURN, yypvt[-0].lnode); } break;
case 72:
# line 255 "lang.y"
{ yyval.lnode = 0; } break;
case 73:
# line 257 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_CONS, yypvt[-0].lnode, 0); } break;
case 74:
# line 259 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_CONS, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 76:
# line 263 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_LOR, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 78:
# line 267 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_LAND, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 80:
# line 271 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_OR, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 82:
# line 275 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_XOR, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 84:
# line 279 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_AND, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 86:
# line 283 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_EQ, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 87:
# line 285 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_NE, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 89:
# line 289 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_GT, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 90:
# line 291 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_GE, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 91:
# line 293 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_LT, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 92:
# line 295 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_LE, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 94:
# line 299 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_LSH, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 95:
# line 301 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_RSH, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 97:
# line 305 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_ADD, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 98:
# line 307 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_SUBTRACT, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 100:
# line 311 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_MULTIPLY, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 101:
# line 313 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_MOD, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 102:
# line 315 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_DIVIDE, yypvt[-2].lnode, yypvt[-0].lnode); } break;
case 104:
# line 319 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_INC, yypvt[-0].lnode); } break;
case 105:
# line 321 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_DEC, yypvt[-0].lnode); } break;
case 106:
# line 323 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_NOT, yypvt[-0].lnode); } break;
case 107:
# line 325 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_COMPL, yypvt[-0].lnode); } break;
case 108:
# line 327 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_NEGATE, yypvt[-0].lnode); } break;
case 110:
# line 331 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_POST_INC, yypvt[-1].lnode); } break;
case 111:
# line 333 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_POST_DEC, yypvt[-1].lnode); } break;
case 116:
# line 336 "lang.y"
{ yyval.lnode = yypvt[-1].lnode; } break;
case 117:
# line 337 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_1(F_AGGREGATE, yypvt[-2].lnode); } break;
case 118:
# line 340 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_number(F_IDENTIFIER,
						    check_deklared(yypvt[-0].string));
						    free(yypvt[-0].string); } break;
case 119:
# line 343 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_single(F_ARGUMENT); } break;
case 121:
# line 346 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_2(F_SUBSCRIPT, yypvt[-3].lnode, yypvt[-1].lnode); } break;
case 122:
# line 349 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_name(F_STRING, yypvt[-0].string); } break;
case 123:
# line 354 "lang.y"
{ 
		    int f;
		    if (defined_function(yypvt[-3].string) || (f = lookup_predef(yypvt[-3].string)) < 0)
		        yyval.lnode = (struct lnode *)alloc_lnode_funcall(F_FUNCTION, yypvt[-3].string, yypvt[-1].lnode); 
		    else
		        yyval.lnode = (struct lnode *)alloc_lnode_1(f, yypvt[-1].lnode);
		} break;
case 124:
# line 362 "lang.y"
{
		    struct lnode *p;
		    p = (struct lnode *)alloc_lnode_name(F_STRING, yypvt[-3].string),
		    p = (struct lnode *)alloc_lnode_2(F_CONS, p, yypvt[-1].lnode);
		    p = (struct lnode *)alloc_lnode_2(F_CONS, yypvt[-5].lnode, p);
		    yyval.lnode = (struct lnode *)alloc_lnode_1(F_CALL_OTHER, p);
		} break;
case 126:
# line 372 "lang.y"
{
		    char *p = xalloc(strlen(yypvt[-0].string) + 3);
		    strcpy(p, "::"); strcat(p, yypvt[-0].string); free(yypvt[-0].string);
		    yyval.string = p;
		} break;
case 127:
# line 474 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_3(F_IF, yypvt[-2].lnode, yypvt[-0].lnode, 0); } break;
case 128:
# line 476 "lang.y"
{ yyval.lnode = (struct lnode *)alloc_lnode_3(F_IF, yypvt[-4].lnode, yypvt[-2].lnode, yypvt[-0].lnode); } break;
	}
	goto yystack;		/* reset registers in driver code */
}
