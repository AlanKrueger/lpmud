#include "../../../room/std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
       ex_init();

THREE_EXIT("players/ringer/pyramid/desert6","north",
          "players/ringer/d_edge","south",
          "players/ringer/pyramid/desert1","west",
          "A vast desolate desert",
"A desert stretches into the distance to the north and west.  To\n"+
"south the desert seems to end.\n",1)

ex_init() {
    add_action("search"); add_verb("search");
}

search(str) {
    if (!str) str = "room";
    if (str == "room") {
        write("You find nothing unusual.\n");
        say(call_other(this_player(),"query_name") + " searches the room.\n");
        return 1;
    }
}




