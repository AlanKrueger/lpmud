# 1 "players/kantele/office.c"
# 1 "/home/lp2/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/kantele/office.c"

reset(arg) {  if (arg) return; set_light(1); } short() { if (set_light(0)) return           "Dusty office"; return "dark room"; } init() { add_action("move", "north");  } move() {  call_other(this_player(), "move_player", "north" + "#" +"players/kantele/trophy_room"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(          "You are in a very dusty office, the only exit is to the north.\n"); write("    The only obvious exit is " + "north" + ".\n"); }
# 6 "players/kantele/office.c"