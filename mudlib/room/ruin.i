# 1 "room/ruin.c"
# 1 "room/std.h"







































































































































































# 2 "room/ruin.c"

id(str)
{
    if (str == "ruin")
	return 1;
    else
	return 0;
}

reset(arg) {  if (arg) return; set_light( 	  1); } short() { if (set_light(0)) return  	  "Ruin"; return "dark room"; } init() { add_action("move1",  "south"); add_action("move2",  "north"); add_action("move3",  "east"); add_action("move4",  "west");  } move1() {  call_other(this_player(), "move_player",  "south" + "#" + "room/plane4"); return 1; } move2() {  call_other(this_player(), "move_player",  "north" + "#" +  	  "room/plane8"); return 1; } move3() {  call_other(this_player(), "move_player",  "east" + "#" +  	  "room/plane9"); return 1; } move4() {  call_other(this_player(), "move_player",  "west" + "#" +  	  "room/plane3"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write( 	  "A very old looking ruin. There is no roof, and no door.\n"); write("There are four obvious exits, " +  "south" + ", " +  "north" + ", " +  "east" + " and " +  "west" + ".\n"); }
# 18 "room/ruin.c"
