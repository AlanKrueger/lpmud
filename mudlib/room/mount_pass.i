# 1 "room/mount_pass.c"
# 1 "room/std.h"







































































































































































# 2 "room/mount_pass.c"





reset(arg) {  if (arg) return; set_light( 1); } short() { if (set_light(0)) return  	 "Mountain pass"; return "dark room"; } init() { add_action("move1",  "south"); add_action("move2",  "north"); add_action("up", "up"); add_action("up", "climb"); } move1() {  call_other(this_player(), "move_player",  "south" + "#" + "room/plane11"); return 1; } move2() {  call_other(this_player(), "move_player",  "north" + "#" +  	 "room/mine/tunnel"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write( 	 "You are in a pass going into the mountain with a steep slope\nupwards to the north.\nHowever, the path is barred.\nThere is a tunnel entrance to the north.\n"+ 	 "It might be possible to climb up, though\n"); write("There are two obvious exits, " +  "south" + " and " +  "north" + ".\n"); }
# 12 "room/mount_pass.c"

up() {
    call_other(this_player(),"move_player", "up#room/ravine");
    return 1;
}
