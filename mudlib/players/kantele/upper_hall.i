# 1 "players/kantele/upper_hall.c"
# 1 "/home/lp2/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/upper_hall.c"

reset(arg) {  if (arg) return; set_light(1); } short() { if (set_light(0)) return           "The second floor hall"; return "dark room"; } init() { add_action("move1", "north"); add_action("move2", "west"); add_action("move3", "east"); add_action("move4", "south");  } move1() {  call_other(this_player(), "move_player", "north" + "#" + "players/kantele/on_roof"); return 1; } move2() {  call_other(this_player(), "move_player", "west" + "#" +           "players/kantele/lab"); return 1; } move3() {  call_other(this_player(), "move_player", "east" + "#" +           "players/kantele/small_room"); return 1; } move4() {  call_other(this_player(), "move_player", "south" + "#" +           "players/kantele/stairway_up"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "You are in the hall on the second floor, to the north you can\n" +          "exit on to the roof. to the south you can see the stairway.\n"); write("There are four obvious exits, " + "north" + ", " + "west" + ", " + "east" + " and " + "south" + ".\n"); }
# 10 "players/kantele/upper_hall.c"