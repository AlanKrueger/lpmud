# 1 "players/kantele/robing_room.c"
# 1 "/home/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/robing_room.c"

reset(arg) {  if (arg) return; set_light(0); } short() { if (set_light(0)) return           "In the robing room"; return "dark room"; } init() { add_action("move", "east");  } move() {  call_other(this_player(), "move_player", "east" + "#" +"players/kantele/behind_altar"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "In a small robing room, tho the east you can see the altar.\n"); write("    The only obvious exit is " + "east" + ".\n"); }
# 6 "players/kantele/robing_room.c"
