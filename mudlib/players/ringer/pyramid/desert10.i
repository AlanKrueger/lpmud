# 1 "players/ringer/pyramid/desert10.c"
# 1 "players/ringer/pyramid/../../../room/std.h"







































































































































































# 2 "players/ringer/pyramid/desert10.c"





reset(arg) {  if (arg) return; set_light(1); } short() { if (set_light(0)) return            "A vast desolate desert"; return "dark room"; } init() { add_action("move1", "south"); add_action("move2", "west"); ex_init(); } move1() {  call_other(this_player(), "move_player", "south" + "#" + "players/ringer/pyramid/desert6"); return 1; } move2() {  call_other(this_player(), "move_player", "west" + "#" +            "players/ringer/pyramid/desert5"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; }  write( "A desert stretches far into the distance to the south and west.\n"); write("There are two obvious exits, " + "south" + " and " + "west" + ".\n"); }
# 12 "players/ringer/pyramid/desert10.c"

ex_init() {
    add_action("search"); add_verb("search");
}

search(str) {
    if (!str) str = "room";
    if (str == "room") {
        write("You find nothing unusual.\n");
        say(call_other(this_player(),"query_name") + " searches the room.\n");
        return 1;
    }
}




