struct sentence {
    char *verb;
    struct object *ob;
    char *function;
    struct sentence *next;
    int short_verb;		/* Only leading characters count */
};

struct sentence *alloc_sentence();

void remove_sent PROT((struct object *, struct object *)),
    free_sentence PROT((struct sentence *));
