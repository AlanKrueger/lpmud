# 1 "players/morgar/slimeworld/pillars.c"

# 1 "/usr/users/jseidman/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/slimeworld/pillars.c"

reset(arg) {  if (arg) return; set_light( 1); }short() {    if (set_light(0))	return 
	 "Ruins of a temple";    return "dark room";}init() {    add_action("move1"); add_verb( "north");    add_action("move2"); add_verb( "east");    }move1() {        call_other(this_player(), "move_player",  "north" + "#" + "players/morgar/slimeworld/ruins");    return 1;}move2() {        call_other(this_player(), "move_player",  "east" + "#" + 
	 "players/morgar/slimeworld/entry");    return 1;}long(str) {    if (set_light(0) == 0){       write("It is dark.\n");       return;    }        write(
	 "You are in what must have once been a temple.  However, slime\n" +
         "has long since eaten away at the stone, leaving only a few pillars.\n");    write("There are two obvious exits, " +  "north" + " and " +  "east" + ".\n");}

realm() {
    return("slime");
}
