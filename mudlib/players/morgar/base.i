# 1 "players/morgar/base.c"
# 1 "/home/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/base.c"

reset(arg) {  if (arg) return; set_light( 1); } short() { if (set_light(0)) return           "Base of the tower"; return "dark room"; } init() { add_action("move1",  "north"); add_action("move2",  "east"); add_action("move3",  "south");  } move1() {  call_other(this_player(), "move_player",  "north" + "#" + "room/clearing"); return 1; } move2() {  call_other(this_player(), "move_player",  "east" + "#" +           "players/morgar/hall"); return 1; } move3() {  call_other(this_player(), "move_player",  "south" + "#" +           "players/morgar/field"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "This is a path that leads north-south around the tower of the gates.\n" +          "The tower itself it to the east.\n"); write("There are three obvious exits, " +  "north" + ", " +  "east" + " and " +  "south" + ".\n"); }
# 9 "players/morgar/base.c"
