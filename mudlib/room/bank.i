# 1 "room/bank.c"
# 1 "room/std.h"







































































































































































# 2 "room/bank.c"
int door_is_open, door_is_locked;
object guard;




extra_reset() {
    if (!guard || !living(guard)) {
	object key, weapon;
        guard = clone_object("obj/monster");
	call_other(guard, "set_name", "guard");
	call_other(guard, "set_level", 11);
	call_other(guard, "set_hp", 200);
	call_other(guard, "set_al", 100);
	call_other(guard, "set_short", "A guard");
	call_other(guard, "set_long", "A big and sturdy guard.");
	move_object(guard, this_object());
	weapon = clone_object("obj/weapon");
	call_other(weapon, "set_name", "shortsword");
	call_other(weapon, "set_short", "A shortsword");
	call_other(weapon, "set_alias", "sword");
	call_other(weapon, "set_long",
"It is proffesional looking short sword, used by warriors and guards");
	call_other(weapon, "set_class", 15);
	call_other(weapon, "set_value",700);
	call_other(weapon, "set_weight", 3);
	transfer(weapon, guard);
	call_other(guard, "init_command", "wield shortsword");
	key = clone_object("obj/treasure");
	call_other(key, "set_id", "key");
	call_other(key, "set_alias", "bank key");
	call_other(key, "set_short", "A bronze key");
	call_other(key, "set_value", 10);
	call_other(key, "set_weight", 1);
	transfer(key, guard);
    }
    door_is_open = 0; door_is_locked = 1;
}
	






















reset(arg) { extra_reset(); if (arg) return; set_light( 1); } short() { if (set_light(0)) return  	 "The bank"; return "dark room"; } init() { add_action("move", "west"); add_action("open", "open"); add_action("unlock", "unlock"); add_action("east", "east"); } move() {  call_other(this_player(), "move_player", "west" + "#" +"room/narr_alley"); return 1; } long(str) { if (set_light(0) == 0){ write("It is dark.\n"); return; } if (str == "counter") { write("There is a sign  in the counter that says\n" + "CLOSED FOR RECONSTRUCTION\n"); return; } if (str == "door") { if (door_is_open) { write("The door is open.\n"); return; } write("The door is closed.\n"); return; } write( 	 "You are in the bank.\n" + 	 "To the east is a low counter. The counter is covered\n" + 	 "with heavy iron bars. On the wall beside the counter, a door\n" + 	 "leads further east\n"); write("    The only obvious exit is " + "west" + ".\n"); }
# 71 "room/bank.c"

id(str) {
    return str == "door" || str == "counter";
}

open(str) {
    if (str && str != "door")
	return 0;
    if (door_is_open)
	return 0;
    if (door_is_locked) {
	write("The door is locked.\n");
	return 1;
    }
    door_is_open = 1;
    write("Ok.\n");
    say(call_other(this_player(), "query_name") + " opened the door.\n");
    return 1;
}

unlock(str) {
    if (str && str != "door")
	return 0;
    if (door_is_open || !door_is_locked)
	return 0;
    if (!present("bank key", this_player())) {
	if (present("key", this_player()))
	    write("You don't have the right key.\n");
	else
	    write("You need a key.\n");
	return 1;
    }
    door_is_locked = 0;
    write("ok.\n");
    say(call_other(this_player(), "query_name") + " unlocked the door.\n");
    return 1;
}

east() {
    if (!door_is_open) {
	write("The door is closed.\n");
	return 1;
    }
    if (guard && present(guard, this_object())) {
	write("The guard bars the way.\n");
	return 1;
   }
    call_other(this_player(), "move_player", "east#room/bankroom");
    return 1;
}

query_door() {
    return !door_is_open;
}

open_door_inside() {
    door_is_locked = 0;
    door_is_open = 1;
}

query_drop_castle() {
    return 1;
}
