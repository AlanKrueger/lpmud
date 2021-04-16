#include "std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
    add_action("regenerate"); add_verb("regenerate");

regenerate() {
     return call_other(this_player(), "remove_ghost");
}

realm() { return "NT"; }

ONE_EXIT("players/crimson/thunderdome", "east",
         "THUNDERWING WEST",
         "You are in the THUNDERWING WEST.\n"+
         "Your things are here and you may 'regenerate'\n"+
         "here if you are a ghost.\n", 1)
