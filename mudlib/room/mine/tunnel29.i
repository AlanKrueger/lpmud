# 1 "room/mine/tunnel29.c"
# 1 "room/mine/../room.h"
inherit "room/room";
























# 2 "room/mine/tunnel29.c"


object dragon;

























reset(arg) { if (!arg) { set_light( 0); short_desc =  	 "Dead end"; long_desc =  	 "Dead end.\n"; dest_dir = ({ "room/mine/tunnel28",  "west" }); } if (!dragon || !living(dragon)) { object treas; dragon = clone_object("obj/monster"); call_other(dragon, "set_name", "dragon"); call_other(dragon, "set_level", 17); call_other(dragon, "set_al", -900); call_other(dragon, "set_short", "The cave dragon"); call_other(dragon, "set_wc", 25); call_other(dragon, "set_ac", 4); treas = clone_object("obj/treasure"); call_other(treas, "set_id", "sapphire"); call_other(treas, "set_alias", "stone"); call_other(treas, "set_short", "A sapphire"); call_other(treas, "set_value", 250); move_object(treas, dragon); treas = clone_object("obj/treasure"); call_other(treas, "set_id", "diamond"); call_other(treas, "set_alias", "stone"); call_other(treas, "set_short", "A diamond"); call_other(treas, "set_value", 250); move_object(treas, dragon); move_object(dragon, this_object()); } }
# 34 "room/mine/tunnel29.c"
