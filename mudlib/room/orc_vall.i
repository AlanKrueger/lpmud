# 1 "room/orc_vall.c"
# 1 "room/room.h"
inherit "room/room";
























# 2 "room/orc_vall.c"



string chats;

get_chats() {
    if (!chats) {
	chats = allocate(7);
	chats[0] = "Orc says: Kill him!\n";
	chats[1] = "Orc says: Bloody humans!\n";
	chats[2] = "Orc says: Stop him!\n";
	chats[3] = "Orc says: Get him!\n";
	chats[4] = "Orc says: Let's rip out his guts!\n";
	chats[5] = "Orc says: Kill him before he runs away!\n";
	chats[6] = "Orc says: What is that human doing here!\n";
    }
    return chats;
}

extra_reset()
{
    object orc, weapon;
    int n,i,class,value,weight;
    string w_name,alt_name;

    i = 0;
    if (!present("orc")) {
	while(i<2) {
	    i += 1;
	    orc = clone_object("obj/monster");
	    call_other(orc, "set_name", "orc");
	    call_other(orc, "set_alias", "dirty crap");
	    call_other(orc, "set_race", "orc");
	    call_other(orc, "set_level", random(2) + 1);
	    call_other(orc, "set_hp", 30);
	    call_other(orc, "set_ep", 1014);
	    call_other(orc, "set_al", -60);
	    call_other(orc, "set_short", "An orc");
	    call_other(orc, "set_ac", 0);
	    call_other(orc, "set_aggressive", 1);
	    call_other(orc, "load_a_chat", 50, get_chats());
	    n = random(3);
	    weapon = clone_object("obj/weapon");
	    if (n == 0) {
		w_name = "knife";
		class = 5;
		value = 8;
		weight = 1;
	    }
	    if (n == 1) {
		w_name = "curved knife";
		class = 7;
		value = 15;
		weight = 1;
		alt_name = "knife";
	    }
	    if (n == 2) {
		w_name = "hand axe";
		class = 9;
		value = 25;
		weight = 2;
		alt_name = "axe";
	    }
	    call_other(weapon, "set_name", w_name);
	    call_other(weapon, "set_class", class);
	    call_other(weapon, "set_value", value);
	    call_other(weapon, "set_weight", weight);
	    call_other(weapon, "set_alt_name", alt_name);
	    transfer(weapon, orc);
	    command("wield " + w_name, orc);
	    move_object(orc, this_object());
	}
    }
}

reset(arg) { if (!arg) { set_light( 1); short_desc =  	 "The orc valley"; long_desc =  	 "You are in the orc valley. This place is inhabited by orcs.\n" + 	 "There is a fortress to the north, with lot of signs of orcs.\n"; dest_dir = ({ "room/slope",  "east",  	 "room/fortress",  "north" }); } extra_reset(); }
# 82 "room/orc_vall.c"
