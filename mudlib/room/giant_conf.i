# 1 "room/giant_conf.c"
# 1 "room/room.h"
inherit "room/room";
























# 2 "room/giant_conf.c"

object giant1, giant2, giant3;

extra_reset() {
    object weapon;
    if (!giant2 || !living(giant2)) {
	giant2 = clone_object("obj/monster");
	call_other(giant2, "set_name", "giant");
	call_other(giant2, "set_alias", "frostgiant");
	call_other(giant2, "set_level", 15);
	call_other(giant2, "set_short", "A frost giant");
	call_other(giant2, "set_wc", 20);
	call_other(giant2, "set_ac", 2);
	call_other(giant2, "set_al", -150);
	call_other(giant2, "set_aggressive", 1);
	move_object(giant2, this_object());
	weapon = clone_object("obj/weapon");
	call_other(weapon, "set_name", "sword");
	call_other(weapon, "set_alias", "sword of frost");
	call_other(weapon, "set_short", "sword of frost");
	call_other(weapon, "set_class", 20);
	call_other(weapon, "set_weight", 3);
	call_other(weapon, "set_value", 2000);
	move_object(weapon, giant2);
    }
    if (!giant3 || !living(giant3)) {
	giant3 = clone_object("obj/monster");
	call_other(giant3, "set_name", "giant");
	call_other(giant3, "set_alias", "stonegiant");
	call_other(giant3, "set_level", 15);
	call_other(giant3, "set_short", "A stone giant");
	call_other(giant3, "set_wc", 20);
	call_other(giant3, "set_ac", 2);
	call_other(giant3, "set_al", -150);
	call_other(giant3, "set_aggressive", 1);
	move_object(giant3, this_object());
	weapon = clone_object("obj/weapon");
	call_other(weapon, "set_name", "sword");
	call_other(weapon, "set_alias", "stone cutter sword");
	call_other(weapon, "set_short", "stone cutter sword");
	call_other(weapon, "set_class", 20);
	call_other(weapon, "set_weight", 3);
	call_other(weapon, "set_value", 2000);
	move_object(weapon, giant3);
    }
    if (!giant1 || !living(giant1)) {
	giant1 = clone_object("obj/monster");
	call_other(giant1, "set_name", "giant");
	call_other(giant1, "set_alias", "firegiant");
	call_other(giant1, "set_level", 15);
	call_other(giant1, "set_short", "A fire giant");
	call_other(giant1, "set_wc", 20);
	call_other(giant1, "set_ac", 2);
	call_other(giant1, "set_al", -150);
	call_other(giant1, "set_aggressive", 1);
	move_object(giant1, this_object());
	weapon = clone_object("obj/weapon");
	call_other(weapon, "set_name", "sword");
	call_other(weapon, "set_alias", "sword of fire");
	call_other(weapon, "set_short", "sword of fire");
	call_other(weapon, "set_class", 20);
	call_other(weapon, "set_weight", 3);
	call_other(weapon, "set_value", 2000);
	move_object(weapon, giant1);
    }
}





reset(arg) { if (!arg) { set_light( 1); short_desc =  	 "Giants conference of human bashing"; long_desc =  	 "You are at the yearly conference of human bashing,\n" + 	 "organized by the giants.\n"; dest_dir = ({ "room/giant_lair",  "east" }); } extra_reset(); }
# 78 "room/giant_conf.c"
