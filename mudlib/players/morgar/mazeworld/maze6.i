# 1 "players/morgar/mazeworld/maze6.c"

# 1 "/usr/users/jseidman/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/mazeworld/maze6.c"

object mirror;

reset(arg) {  if (arg) return; set_light( 1); }short() {    if (set_light(0))	return 
	 "Dead end corridor";    return "dark room";}init() {    add_action("move"); add_verb( "west");    }move() {        call_other(this_player(), "move_player",  "west" + "#" +"players/morgar/mazeworld/maze2");    return 1;}long(str) {    if (set_light(0) == 0){       write("It is dark.\n");       return;    }        write(
	 "You at the end of an east-west corridor.  The air glows faintly here.\n");    write("    The only obvious exit is " +  "west" + ".\n");}

realm() {
    return("maze");
}
