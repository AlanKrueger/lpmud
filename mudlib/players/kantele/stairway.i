# 1 "players/kantele/stairway.c"
# 1 "/home/lp2/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/stairway.c"

reset(arg) {  if (arg) return; set_light(1); } short() { if (set_light(0)) return           "A landing in stairway"; return "dark room"; } init() { add_action("move1", "north"); add_action("move2", "up"); add_action("move3", "down");  } move1() {  call_other(this_player(), "move_player", "north" + "#" + "players/kantele/inner_hall"); return 1; } move2() {  call_other(this_player(), "move_player", "up" + "#" +           "players/kantele/stairway_up"); return 1; } move3() {  call_other(this_player(), "move_player", "down" + "#" +           "players/kantele/stairway_down"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "You are in a landing on the stairway, the stairway goes up\n" +          "and it disapears down into the darkness, an passage leads north.\n"); write("There are three obvious exits, " + "north" + ", " + "up" + " and " + "down" + ".\n"); }
# 9 "players/kantele/stairway.c"
