# 1 "players/kantele/dirty_passage.c"
# 1 "/home/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/dirty_passage.c"

reset(arg) {  if (arg) return; set_light(0); } short() { if (set_light(0)) return           "You are in a narrow corridor"; return "dark room"; } init() { add_action("move1", "south"); add_action("move2", "north");  } move1() {  call_other(this_player(), "move_player", "south" + "#" + "players/kantele/cellar_west"); return 1; } move2() {  call_other(this_player(), "move_player", "north" + "#" +           "players/kantele/dirty_corridor"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "You are in a narrow corridor, it is damp and dark.\n"); write("There are two obvious exits, " + "south" + " and " + "north" + ".\n"); }
# 7 "players/kantele/dirty_passage.c"