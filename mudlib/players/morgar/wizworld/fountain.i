# 1 "players/morgar/wizworld/fountain.c"
id(str) { return str == "fountain"; }

long() {
    write("A magnificent fountain is here.  Crystal clear water falls\n");
    write("in complex patters over an abstract sculpture.\n");
}

short() { return "A magnificent fountain is here"; }

get() { return 0; }

query_name() {
   return "fountain";
}
