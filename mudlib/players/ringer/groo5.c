#include "../../room/std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
       ex_init();

#undef EXTRA_RESET
#define EXTRA_RESET\
        my_reset();

#undef EXTRA_LONG
#define EXTRA_LONG\
      ex_long();

ONE_EXIT("players/ringer/groo4", "west",
	   "You are in a dead end",
"The tunnel dead ends here.\n",0)

int passage;

ex_init() {
    add_action("north"); add_verb("north");
    add_action("search"); add_verb("search");
}

search(str) {
    if (!str) str = "room";
    if (str == "room") {
        write("A careful search of the room reveals a secret passage leading north.\n");
        say(call_other(this_player(),"query_name") + " finds a secret passage leading north.\n");
        passage = 1;
        return 1;
    }
}

ex_long(){
    if (passage) write("There is passage leading north.\n");
}

north() {
   if (passage) {
       call_other(this_player(),"move_player","north#players/ringer/trap1");
       return 1;
   }
   return 0;
}

my_reset() {
    passage=0;
}    
