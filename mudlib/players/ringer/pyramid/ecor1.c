#include "../../../room/std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
       ex_init();

TWO_EXIT("players/ringer/pyramid/ecor2","east",
         "players/ringer/pyramid/sjnct","west",
         "East/west corridor",
"The corridor continues east and west here.  The walls are smooth and\n"+
"uniform and somewhat dusty.\n",0)

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
