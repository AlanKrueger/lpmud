# 1 "players/jeff/workroom.c"
# 1 "/home/lp2/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/jeff/workroom.c"




reset(arg) { extra_reset(); if (arg) return; set_light( 1); } short() { if (set_light(0)) return            "Jeff's residence"; return "dark room"; } init() { add_action("move1",  "north"); add_action("move2",  "west");  } move1() {  call_other(this_player(), "move_player",  "north" + "#" + "room/ruin"); return 1; } move2() {  call_other(this_player(), "move_player",  "west" + "#" +           "room/pub2"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write(           "Jeff's workroom. To the north is a ruin, west a pub.\n"); write("There are two obvious exits, " +  "north" + " and " +  "west" + ".\n"); }
# 10 "players/jeff/workroom.c"


object tracer;

extra_reset() {
    if (!tracer) {
	tracer = clone_object("/obj/trace");
	move_object(tracer, this_object());
    }
}
