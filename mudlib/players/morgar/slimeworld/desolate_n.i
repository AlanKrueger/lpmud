# 1 "players/morgar/slimeworld/desolate_n.c"

# 1 "/usr/users/jseidman/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/slimeworld/desolate_n.c"

reset(arg) {  if (arg) return; set_light( 1); }short() {    if (set_light(0))	return 
	 "The slime plain";    return "dark room";}init() {    add_action("move1"); add_verb( "south");    add_action("move2"); add_verb( "east");    add_action("move3"); add_verb( "west");    }move1() {        call_other(this_player(), "move_player",  "south" + "#" + "players/morgar/slimeworld/desolate");    return 1;}move2() {        call_other(this_player(), "move_player",  "east" + "#" + 
	 "players/morgar/slimeworld/desolate_2n");    return 1;}move3() {        call_other(this_player(), "move_player",  "west" + "#" + 
	 "players/morgar/slimeworld/mound");    return 1;}long(str) {    if (set_light(0) == 0){       write("It is dark.\n");       return;    }        write(
	 "You are in a vast plain, covered with dried slime.  The plain\n" +
         "seems to stretch on and on, with nothing of note except for a\n" +
         "small object on the horzon to the southeast, and the stuff near\n" +
         "the mirror to the southwest.\n");    write("There are three obvious exits, " +  "south" + ", " +  "east" +	  " and " +  "west" + ".\n");}

realm() {
    return("slime");
}