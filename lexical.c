# include "stdio.h"
# define U(x) ((unsigned char)(x))
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) (void)putc(c,yyout)
#if defined(__cplusplus) || defined(__STDC__)
	int yyback(int *, int);
	int yyinput(void);
	int yylook(void);
	void yyoutput(int);
	int yyracc(int);
	int yyreject(void);
	void yyunput(int);

#ifndef __STDC__
#ifndef yyless
	void yyless(int);
#endif
#ifndef yywrap
	int yywrap(void);
#endif
#endif

#endif
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO (void)fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

# line 2 "lexical.l"
	/* next error will still return 1 by default */

# line 4 "lexical.l"
/* #include "lint.h" */
#include "y.tab.h"
#include "string.h"
#include "lnode.h"
#include "config.h"


# line 10 "lexical.l"
/*
 * Flex doesn't handle negative characters, but this change will at least
 * not crash the game.
 */
#ifdef YY_FATAL_ERROR
#undef YY_FATAL_ERROR
#define YY_FATAL_ERROR(msg) \
	{ \
	fputs( msg, stderr ); \
	putc( '\n', stderr ); \
	error(msg); \
	}
#endif

#define RESBIT 0x4000

int current_line;
int total_lines;	/* Used to compute average compiled lines/s */
char *current_file;
extern char *argument_name;
int number(), ident(), string(), atoi();
static int lookupword();
static int islocal();

#ifdef FLEX
#define yywrap() 1
#endif

extern char *local_names[];
extern int current_number_of_locals;

extern char *string_copy();

void pre_processor_info(), yyerror(), error(), free();
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 48 "lexical.l"
{ return ';'; }
break;
case 2:

# line 49 "lexical.l"
{ return '('; }
break;
case 3:

# line 50 "lexical.l"
{ return ')'; }
break;
case 4:

# line 51 "lexical.l"
{ return ','; }
break;
case 5:

# line 52 "lexical.l"
{ return '{'; }
break;
case 6:

# line 53 "lexical.l"
{ return '}'; }
break;
case 7:

# line 54 "lexical.l"
{ return F_INC; }
break;
case 8:

# line 55 "lexical.l"
{ return F_DEC; }
break;
case 9:

# line 56 "lexical.l"
{ return '~'; }
break;
case 10:

# line 57 "lexical.l"
{ return '&'; }
break;
case 11:

# line 58 "lexical.l"
{ return F_AND_EQ; }
break;
case 12:

# line 59 "lexical.l"
{ return '|'; }
break;
case 13:

# line 60 "lexical.l"
{ return F_OR_EQ; }
break;
case 14:

# line 61 "lexical.l"
{ return '^'; }
break;
case 15:

# line 62 "lexical.l"
{ return F_XOR_EQ; }
break;
case 16:

# line 63 "lexical.l"
{ return F_LSH; }
break;
case 17:

# line 64 "lexical.l"
{ return F_LSH_EQ; }
break;
case 18:

# line 65 "lexical.l"
{ return F_RSH; }
break;
case 19:

# line 66 "lexical.l"
{ return F_RSH_EQ; }
break;
case 20:

# line 67 "lexical.l"
{ return F_NOT; }
break;
case 21:

# line 68 "lexical.l"
{ return F_LAND; }
break;
case 22:

# line 69 "lexical.l"
{ return F_LOR; }
break;
case 23:

# line 70 "lexical.l"
{ return F_ARROW; }
break;
case 24:

# line 71 "lexical.l"
{ return '='; }
break;
case 25:

# line 72 "lexical.l"
{ return '-'; }
break;
case 26:

# line 73 "lexical.l"
{ return F_SUB_EQ; }
break;
case 27:

# line 74 "lexical.l"
{ return '+'; }
break;
case 28:

# line 75 "lexical.l"
{ return F_ADD_EQ; }
break;
case 29:

# line 76 "lexical.l"
{ return '*'; }
break;
case 30:

# line 77 "lexical.l"
{ return F_MULT_EQ; }
break;
case 31:

# line 78 "lexical.l"
{ return '%'; }
break;
case 32:

# line 79 "lexical.l"
{ return F_MOD_EQ; }
break;
case 33:

# line 80 "lexical.l"
{ return '/'; }
break;
case 34:

# line 81 "lexical.l"
{ return F_DIV_EQ; }
break;
case 35:

# line 82 "lexical.l"
{ return '<'; }
break;
case 36:

# line 83 "lexical.l"
{ return '>'; }
break;
case 37:

# line 84 "lexical.l"
{ return F_GE; }
break;
case 38:

# line 85 "lexical.l"
{ return F_LE; }
break;
case 39:

# line 86 "lexical.l"
{ return F_EQ; }
break;
case 40:

# line 87 "lexical.l"
{ return F_NE; }
break;
case 41:

# line 88 "lexical.l"
{ return F_COLON_COLON; }
break;
case 42:

# line 89 "lexical.l"
{ pre_processor_info(yytext); }
break;
case 43:

# line 90 "lexical.l"
{ return '['; }
break;
case 44:

# line 91 "lexical.l"
{ return ']'; }
break;
case 45:

# line 92 "lexical.l"
{ return number(yytext); }
break;
case 46:

# line 93 "lexical.l"
{ yylval.lnode = (struct lnode *)alloc_lnode_number(F_NUMBER,
							    yytext[1]);
          return F_NUMBER; }
break;
case 47:

# line 96 "lexical.l"
{ 
          int r;

          r = lookup_resword(yytext);
          if (r >= 0) {
             return r;
          } else
             return ident(yytext);
        }
break;
case 48:

# line 105 "lexical.l"
   { return string(yytext); }
break;
case 49:

# line 106 "lexical.l"
{ break; }
break;
case 50:

# line 107 "lexical.l"
{ current_line++;
	  if (current_line & L_MASK) {
	      yyerror("Too many lines.\n");
	      current_line = 0;
	  }
	  total_lines++;
	}
break;
case 51:

# line 114 "lexical.l"
{ char buff[100]; sprintf(buff, "Illegal character '%c'", yytext[0]);
	  yyerror(buff); }
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

char *xalloc();

extern YYSTYPE yylval;

#ifdef LEX
int yywrap() { return 1; }
#endif

static int islocal(str)
    char *str;
{
    int i;

    for (i=current_number_of_locals-1; i>=0; i--) {
	if (strcmp(local_names[i], str) == 0)
            return i;
    }
    return -1;
}

int ident(str)
    char *str;
{
    int i;
   
    i = islocal(str);
    if (i >= 0) {
        yylval.lnode = (struct lnode *)alloc_lnode_number(F_LOCAL_NAME, i);
        return F_LOCAL_NAME;
    }
/*
    if (argument_name && strcmp(str, argument_name) == 0)
	return F_ARGUMENT;
*/
    yylval.string = string_copy(str);
    return F_IDENTIFIER;
}

int string(str)
    char *str;
{
    char *p;

    p = xalloc(strlen(str) - 1);
    yylval.string = p;
    for (str++; str[1] != '\0'; str++, p++) {
	if (str[0] == '\\' && str[1] == 'n') {
	    *p = '\n';
	    str++;
	} else if (str[0] == '\\' && str[1] == 't') {
	    *p = '\t';
	    str++;
	} else if (str[0] == '\\' && str[1] == '"') {	/* LA */
	    *p = '"';					/* LA */
	    str++;					/* LA */
	    if (!str[1]) {
		yyerror("Unterminated string");
		break;
	    }
	} else if (str[0] == '\\') {
	    *p = str[1];
	    str++;
	} else
	    *p = *str;
    }
    *p = '\0';
    return F_STRING;
}

int number(str)
    char *str;
{
    int i;

    i = atoi(str);
    if (i == 0) {
        yylval.lnode = (struct lnode *)alloc_lnode_single(F_CONST0);
	return F_CONST0;
    } else if (i == 1) {
	yylval.lnode = (struct lnode *)alloc_lnode_single(F_CONST1);
	return F_CONST1;
    }
    yylval.lnode =(struct lnode *)alloc_lnode_number(F_NUMBER, atoi(str));
    return F_NUMBER;
}

void start_new_file(f)
    FILE *f;
{
#ifdef FLEX
    yy_init = 1;
#endif
#ifdef LEX
    extern int yyprevious;	/* KLUDGE! */
    NLSTATE;
    yysptr = yysbuf;
#endif
    yyin = f;
}

void pre_processor_info(str)
    char *str;
{
    int line, i;
    char file[100];
    if (sscanf(str, "# %d \"%s\"", &line, file) != 2)
	return;
    i = strlen(file);
    if (file[i-1] == '"')
	file[i-1] = '\0';
    free(current_file);
    current_file = string_copy(file);
    current_line = line - 1;
}

static struct keyword {
    char *word;
    int  token;
} predefs[] = {
{ "add_action",		F_ADD_ACTION, },
{ "add_adj",		F_ADD_ADJ, },
{ "add_subst",		F_ADD_SUBST, },
{ "add_verb",		F_ADD_VERB, },
{ "add_worth",		F_ADD_WORTH, },
{ "allocate",		F_ALLOCATE, },
{ "call_other",		F_CALL_OTHER, },
{ "call_out",		F_CALL_OUT, },
{ "capitalize",		F_CAPITALIZE, },
{ "cat",		F_CAT, },
{ "catch",		F_CATCH, },
{ "clear_bit",		F_CLEAR_BIT, },
{ "clone_object",	F_CLONE_OBJECT, },
{ "combine_free_list",	F_COMBINE_FREE_LIST, },
{ "command",		F_COMMAND, },
{ "create_wizard",	F_CREATE_WIZARD, },
{ "creator",		F_CREATOR, },
{ "crypt",		F_CRYPT, },
{ "ctime",		F_CTIME, },
{ "destruct",		F_DESTRUCT, },
{ "disable_commands",	F_DISABLE_COMMANDS, },
{ "ed",			F_ED, },
{ "enable_commands",	F_ENABLE_COMMANDS, },
{ "environment",	F_ENVIRONMENT, },
{ "explode",		F_EXPLODE, },
{ "extract",		F_EXTRACT, },
{ "file_name",		F_FILE_NAME, },
{ "file_size",		F_FILE_SIZE, },
{ "filter_objects",	F_FILTER_OBJECTS, },
{ "find_living",	F_FIND_LIVING, },
{ "find_object",	F_FIND_OBJECT, },
{ "find_player",	F_FIND_PLAYER, },
{ "first_inventory",	F_FIRST_INVENTORY, },
{ "implode",		F_IMPLODE, },
{ "input_to",		F_INPUT_TO, },
{ "intp",		F_INTP, },
{ "living",		F_LIVING, },
{ "localcmd",		F_LOCALCMD, },
{ "log_file",		F_LOG_FILE, },
{ "lower_case",		F_LOWER_CASE, },
{ "ls",			F_LS, },
{ "mkdir",		F_MKDIR, },
{ "move_object",	F_MOVE_OBJECT, },
{ "next_inventory",	F_NEXT_INVENTORY, },
{ "notify_fail",	F_NOTIFY_FAIL, },
{ "objectp",		F_OBJECTP, },
{ "parse_command",	F_PARSE_COMMAND, },
{ "people",		F_PEOPLE, },
{ "pointerp",		F_POINTERP, },
{ "present",		F_PRESENT, },
{ "previous_object",	F_PREVIOUS_OBJECT, },
{ "query_host_name",	F_QUERY_HOST_NAME, },
{ "query_idle",		F_QUERY_IDLE, },
{ "query_ip_number",	F_QUERY_IP_NUMBER, },
{ "query_load_average",	F_QUERY_LOAD_AVERAGE, },
{ "query_snoop",	F_QUERY_SNOOP, },
{ "query_verb",		F_QUERY_VERB, },
{ "random",		F_RANDOM, },
{ "regcomp",		F_REGCOMP, },
{ "regexec",		F_REGEXEC, },
{ "remove_call_out",	F_REMOVE_CALL_OUT, },
{ "restore_object",	F_RESTORE_OBJECT, },
{ "rm",			F_RM, },
{ "rmdir",		F_RMDIR, },
{ "rusage",		F_RUSAGE, },
{ "save_object",	F_SAVE_OBJECT, },
{ "say",		F_SAY, },
{ "set_bit",		F_SET_BIT, },
{ "set_heart_beat",	F_SET_HEART_BEAT, },
{ "set_light",		F_SET_LIGHT, },
{ "set_living_name",	F_SET_LIVING_NAME, },
{ "shout",		F_SHOUT, },
{ "shutdown",		F_SHUTDOWN, },
{ "sizeof",		F_SIZEOF, },
{ "snoop",		F_SNOOP, },
{ "sscanf",		F_SSCANF, },
{ "stringp",		F_STRINGP, },
{ "strlen",		F_STRLEN, },
{ "swap",		F_SWAP, },
{ "tail",		F_TAIL, },
{ "tell_object",	F_TELL_OBJECT, },
{ "tell_room",		F_TELL_ROOM, },
{ "test_bit",		F_TEST_BIT, },
{ "this_object",	F_THIS_OBJECT, },
{ "this_player",	F_THIS_PLAYER, },
{ "throw",		F_THROW, },
{ "time",		F_TIME, },
{ "transfer",		F_TRANSFER, },
{ "users",		F_USERS, },
{ "wizlist",		F_WIZLIST, },
{ "write",		F_WRITE, },
{ "write_file",		F_WRITE_FILE, },
};
#define NELEM(a) (sizeof (a) / sizeof (a)[0])

static struct keyword reswords[] = {
{ "break",		F_BREAK, },
{ "continue",		F_CONTINUE, },
{ "do",			F_DO, },
{ "else",		F_ELSE, },
{ "for",		F_FOR, },
{ "if",			F_IF, },
{ "inherit",		F_INHERIT, },
{ "int",		F_INT, },
{ "object",		F_STATUS, },
{ "return",		F_RETURN, },
{ "static",		F_STATIC, },
{ "status",		F_STATUS, },
{ "string",		F_STRING_DECL, },
{ "while",		F_WHILE, },
};

int
lookupword(s, words, h)
char *s;
struct keyword *words;
int h;
{
    int i, l, r;

    l = 0;
    for(;;) {
      i = (l+h)/2;
      r = strcmp(s, words[i].word);
      if (r == 0)
          return words[i].token;
      else if (l == i)
          return -1;
      else if (r < 0)
          h = i;
      else
          l = i;
    }
}

int lookup_resword(s)
    char *s;
{
    return lookupword(s, reswords, NELEM(reswords));
}

int lookup_predef(s)
    char *s;
{
    return lookupword(s, predefs, NELEM(predefs));
}

#if 0
"ls"	{ return F_LS; }
"cat"	{ return F_CAT; }
query_snoop { return F_QUERY_SNOOP; }
set_bit	    { return F_SET_BIT; }
clear_bit   { return F_CLEAR_BIT; }
test_bit    { return F_TEST_BIT; }
catch	    { return F_CATCH; }
throw	    { return F_THROW; }
filter_objects { return F_FILTER_OBJECTS; }
"rm"	{ return F_RM; }
"log_file" { return F_LOG_FILE; }
write_file { return F_WRITE_FILE; }
file_size  { return F_FILE_SIZE; }
"else"	{ return F_ELSE; }
"find_living" { return F_FIND_LIVING; }
find_player   { return F_FIND_PLAYER; }
"previous_object" { return F_PREVIOUS_OBJECT; }
"inherit"     { return F_INHERIT; }
"tell_object" { return F_TELL_OBJECT; }
"people" { return F_PEOPLE; }
parse_command   { return F_PARSE_COMMAND; }
set_living_name { return F_SET_LIVING_NAME; }
query_host_name { return F_QUERY_HOST_NAME; }
tail	 { return F_TAIL; }
file_name { return F_FILE_NAME; }
query_verb { return F_QUERY_VERB; }
"snoop" { return F_SNOOP; }
"input_to" { return F_INPUT_TO; }
"wizlist" { return F_WIZLIST; }
rmdir   { return F_RMDIR; }
mkdir   { return F_MKDIR; }
"crypt" { return F_CRYPT; }
"first_inventory" { return F_FIRST_INVENTORY; }
"regcomp"	 { return F_REGCOMP; }
"regexec"	 { return F_REGEXEC; }
"transfer"	 { return F_TRANSFER; }
"next_inventory" { return F_NEXT_INVENTORY; }
"string" { return F_STRING_DECL; }
"shout"	{ return F_SHOUT; }
"sscanf" { return F_SSCANF; }
"extract" { return F_EXTRACT; }
"ed"	{ return F_ED; }
"localcmd" { return F_LOCALCMD; }
"swap"	{ return F_SWAP; }
explode { return F_EXPLODE; }
implode { return F_IMPLODE; }
query_idle { return F_QUERY_IDLE; }
notify_fail { return F_NOTIFY_FAIL; }
query_load_average { return F_QUERY_LOAD_AVERAGE; }
"break"	{ return F_BREAK; }
intp	{ return F_INTP; }
pointerp { return F_POINTERP; }
objectp  { return F_OBJECTP; }
stringp  { return F_STRINGP; }
users   { return F_USERS; }
"ctime" { return F_CTIME; }
"disable_commands"  { return F_DISABLE_COMMANDS; }
"allocate"	    { return F_ALLOCATE; }
"combine_free_list" { return F_COMBINE_FREE_LIST; }
"continue" { return F_CONTINUE; }
"while"	{ return F_WHILE; }
"do"	{ return F_DO; }
"for"	{ return F_FOR; }
"capitalize" { return F_CAPITALIZE; }
"living" { return F_LIVING; }
"lower_case" { return F_LOWER_CASE; }
"set_heart_beat" { return F_SET_HEART_BEAT; }
"strlen" { return F_STRLEN; }
"say"	{ return F_SAY; }
"tell_room"	{ return F_TELL_ROOM; }
"find_object"   { return F_FIND_OBJECT; }
"add_worth"	{ return F_ADD_WORTH; }
"time"		{ return F_TIME; }
"create_wizard" { return F_CREATE_WIZARD; }
"destruct" { return F_DESTRUCT; }
"static"   { return F_STATIC; }
"environment" { return F_ENVIRONMENT; }
"save_object" { return F_SAVE_OBJECT; }
"enable_commands" { return F_ENABLE_COMMANDS; }
"sizeof" { return F_SIZEOF; }
"random" { return F_RANDOM; }
"restore_object" { return F_RESTORE_OBJECT; }
"this_object" { return F_THIS_OBJECT; }
"clone_object" { return F_CLONE_OBJECT; }
"this_player" { return F_THIS_PLAYER; }
"if"	{ return F_IF; }
"status" { return F_STATUS; }
"object" { return F_STATUS; }
"return" { return F_RETURN; }
"write" { return F_WRITE; }
"add_verb" { return F_ADD_VERB; }
"add_adj" { return F_ADD_ADJ; }
"add_subst" { return F_ADD_SUBST; }
"add_action" { return F_ADD_ACTION; }
"move_object" { return F_MOVE_OBJECT; }
"present" { return F_PRESENT; }
"call_out" { return F_CALL_OUT; }
"remove_call_out" { return F_REMOVE_CALL_OUT; }
"creator" { return F_CREATOR; }
"query_ip_number" { return F_QUERY_IP_NUMBER; }
"command" { return F_COMMAND; }
"set_light" { return F_SET_LIGHT; }
"int"	{ return F_INT; }
"call_other" { return F_CALL_OTHER; }
"shutdown" { return F_SHUTDOWN; }
#endif
int yyvstop[] = {
0,

51,
0,

49,
51,
0,

50,
0,

20,
51,
0,

51,
0,

31,
51,
0,

10,
51,
0,

51,
0,

2,
51,
0,

3,
51,
0,

29,
51,
0,

27,
51,
0,

4,
51,
0,

25,
51,
0,

33,
51,
0,

45,
51,
0,

51,
0,

1,
51,
0,

35,
51,
0,

24,
51,
0,

36,
51,
0,

47,
51,
0,

43,
51,
0,

44,
51,
0,

14,
51,
0,

5,
51,
0,

12,
51,
0,

6,
51,
0,

9,
51,
0,

51,
-42,
0,

40,
0,

48,
0,

32,
0,

21,
0,

11,
0,

30,
0,

7,
0,

28,
0,

8,
0,

26,
0,

23,
0,

34,
0,

45,
0,

41,
0,

16,
0,

38,
0,

39,
0,

37,
0,

18,
0,

47,
0,

15,
0,

13,
0,

22,
0,

-42,
0,

42,
0,

48,
0,

46,
0,

17,
0,

19,
0,
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
10,40,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,4,	1,5,	
10,40,	10,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
7,34,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
7,34,	7,0,	0,0,	0,0,	
0,0,	34,0,	1,6,	1,7,	
61,0,	10,40,	1,8,	1,9,	
1,10,	1,11,	1,12,	1,13,	
1,14,	1,15,	1,16,	9,38,	
1,17,	1,18,	40,62,	10,40,	
0,0,	7,35,	14,42,	0,0,	
0,0,	0,0,	0,0,	1,19,	
1,20,	1,21,	1,22,	1,23,	
6,33,	8,37,	1,24,	7,34,	
10,40,	13,41,	9,39,	2,6,	
14,43,	2,32,	16,44,	2,8,	
2,9,	2,10,	2,11,	2,12,	
2,13,	2,14,	2,15,	2,16,	
7,34,	2,17,	17,47,	19,49,	
21,50,	21,51,	16,45,	16,46,	
1,25,	22,52,	1,26,	1,27,	
2,19,	2,20,	2,21,	2,22,	
2,23,	18,48,	18,48,	18,48,	
18,48,	18,48,	18,48,	18,48,	
18,48,	18,48,	18,48,	7,36,	
23,53,	23,54,	27,56,	34,36,	
50,63,	54,64,	61,36,	0,0,	
0,0,	0,0,	0,0,	0,0,	
1,28,	1,29,	1,30,	1,31,	
29,57,	2,25,	0,0,	2,26,	
2,27,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	0,0,	0,0,	
0,0,	2,28,	2,29,	2,30,	
2,31,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	29,58,	
0,0,	0,0,	0,0,	24,55,	
0,0,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	24,55,	
24,55,	24,55,	24,55,	32,59,	
36,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	32,59,	
32,60,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
36,61,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
32,59,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	32,59,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	32,59,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	36,36,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-38,	yysvec+1,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+6,
yycrank+3,	0,		yyvstop+8,
yycrank+-19,	0,		yyvstop+11,
yycrank+4,	0,		yyvstop+13,
yycrank+9,	0,		yyvstop+16,
yycrank+-3,	0,		yyvstop+19,
yycrank+0,	0,		yyvstop+21,
yycrank+0,	0,		yyvstop+24,
yycrank+8,	0,		yyvstop+27,
yycrank+11,	0,		yyvstop+30,
yycrank+0,	0,		yyvstop+33,
yycrank+29,	0,		yyvstop+36,
yycrank+25,	0,		yyvstop+39,
yycrank+53,	0,		yyvstop+42,
yycrank+29,	0,		yyvstop+45,
yycrank+0,	0,		yyvstop+47,
yycrank+28,	0,		yyvstop+50,
yycrank+32,	0,		yyvstop+53,
yycrank+51,	0,		yyvstop+56,
yycrank+100,	0,		yyvstop+59,
yycrank+0,	0,		yyvstop+62,
yycrank+0,	0,		yyvstop+65,
yycrank+53,	0,		yyvstop+68,
yycrank+0,	0,		yyvstop+71,
yycrank+67,	0,		yyvstop+74,
yycrank+0,	0,		yyvstop+77,
yycrank+0,	0,		yyvstop+80,
yycrank+-222,	0,		yyvstop+83,
yycrank+0,	0,		yyvstop+86,
yycrank+-23,	yysvec+7,	0,	
yycrank+0,	0,		yyvstop+88,
yycrank+-214,	yysvec+7,	0,	
yycrank+0,	0,		yyvstop+90,
yycrank+0,	0,		yyvstop+92,
yycrank+0,	0,		yyvstop+94,
yycrank+11,	0,		0,	
yycrank+0,	0,		yyvstop+96,
yycrank+0,	0,		yyvstop+98,
yycrank+0,	0,		yyvstop+100,
yycrank+0,	0,		yyvstop+102,
yycrank+0,	0,		yyvstop+104,
yycrank+0,	0,		yyvstop+106,
yycrank+0,	0,		yyvstop+108,
yycrank+0,	yysvec+18,	yyvstop+110,
yycrank+0,	0,		yyvstop+112,
yycrank+55,	0,		yyvstop+114,
yycrank+0,	0,		yyvstop+116,
yycrank+0,	0,		yyvstop+118,
yycrank+0,	0,		yyvstop+120,
yycrank+56,	0,		yyvstop+122,
yycrank+0,	yysvec+24,	yyvstop+124,
yycrank+0,	0,		yyvstop+126,
yycrank+0,	0,		yyvstop+128,
yycrank+0,	0,		yyvstop+130,
yycrank+0,	yysvec+32,	yyvstop+132,
yycrank+0,	0,		yyvstop+134,
yycrank+-26,	yysvec+7,	yyvstop+136,
yycrank+0,	0,		yyvstop+138,
yycrank+0,	0,		yyvstop+140,
yycrank+0,	0,		yyvstop+142,
0,	0,	0};
struct yywork *yytop = yycrank+306;
struct yysvf *yybgin = yysvec+1;
unsigned char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,'A' ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#ident	"@(#)libl:lib/ncform	1.7"
int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
#if defined(__cplusplus) || defined(__STDC__)
int yylook(void)
#else
yylook()
#endif
{
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			if(yylastch > &yytext[YYLMAX]) {
				fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
				exit(1);
			}
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__cplusplus) || defined(__STDC__)
int yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
	if (p==0) return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
	return(0);
}
	/* the following are only used in the lex library */
#if defined(__cplusplus) || defined(__STDC__)
int yyinput(void)
#else
yyinput()
#endif
{
	return(input());
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyoutput(int c)
#else
yyoutput(c)
  int c; 
#endif
{
	output(c);
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyunput(int c)
#else
yyunput(c)
   int c; 
#endif
{
	unput(c);
	}
