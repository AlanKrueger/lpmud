# 1 "players/kantele/courtyard.c"
# 1 "/home/lp2/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/courtyard.c"
reset(arg) {  if (arg) return; set_light(1); } short() { if (set_light(0)) return           "A small courtyard"; return "dark room"; } init() { add_action("move1",  "north"); add_action("move2",  "east" ); add_action("move3",  "west"); add_action("move4",  "south");  } move1() {  call_other(this_player(), "move_player",  "north" + "#" + "players/kantele/brick_road" ); return 1; } move2() {  call_other(this_player(), "move_player",  "east"  + "#" +           "players/kantele/shack" ); return 1; } move3() {  call_other(this_player(), "move_player",  "west" + "#" +           "players/kantele/wagon_stall" ); return 1; } move4() {  call_other(this_player(), "move_player",  "south" + "#" +           "players/kantele/inner_courtyard" ); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "A small courtyard, a road leads north, to the east you can see \n" +          "a small shack. to the west a small open wagon stall can be seen \n" +          "while to the south the entrance to the mansion can be seen \n"); write("There are four obvious exits, " +  "north" + ", " +  "east"  + ", " +  "west" + " and " +  "south" + ".\n"); }
# 10 "players/kantele/courtyard.c"