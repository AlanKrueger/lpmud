# 1 "players/morgar/techworld/blockage.c"

# 1 "/usr/users/jseidman/lpmud/mudlib/room/std.h"







































































































































































# 2 "players/morgar/techworld/blockage.c"

reset(arg) {  if (arg) return; set_light( 1); }short() {    if (set_light(0))	return 
	 "An abandoned alley";    return "dark room";}init() {    add_action("move"); add_verb( "south");    }move() {        call_other(this_player(), "move_player",  "south" + "#" +"players/morgar/techworld/entry");    return 1;}long(str) {    if (set_light(0) == 0){       write("It is dark.\n");       return;    }        write(
	 "You are in the middle of an alley in the ruined city.  At this point,\n" +
         "however, a fallen skyscraper entirely blocks passage.\n");    write("    The only obvious exit is " +  "south" + ".\n");}

realm() { return("tech"); }
