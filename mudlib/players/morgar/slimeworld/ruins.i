# 1 "players/morgar/slimeworld/ruins.c"

# 1 "/usr/users/jseidman/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/slimeworld/ruins.c"

reset(arg) {  if (arg) return; set_light( 1); }short() {    if (set_light(0))	return 
	 "Ruins of a temple";    return "dark room";}init() {    add_action("move1"); add_verb( "south");    add_action("move2"); add_verb( "east");    add_action("move3"); add_verb( "down");    }move1() {        call_other(this_player(), "move_player",  "south" + "#" + "players/morgar/slimeworld/pillars");    return 1;}move2() {        call_other(this_player(), "move_player",  "east" + "#" + 
	 "players/morgar/slimeworld/mound");    return 1;}move3() {        call_other(this_player(), "move_player",  "down" + "#" + 
	 "players/morgar/slimeworld/crypt");    return 1;}long(str) {    if (set_light(0) == 0){       write("It is dark.\n");       return;    }        write(
	 "You are in what was once a temple.  However, slime has long since\n" +
         "eaten away at the stone, leaving decayed ruins.\n");    write("There are three obvious exits, " +  "south" + ", " +  "east" +	  " and " +  "down" + ".\n");}

realm() {
    return("slime");
}