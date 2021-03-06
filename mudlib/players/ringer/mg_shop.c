#include "../../room/std.h"

#undef EXTRA_INIT
#define EXTRA_INIT\
    add_action("sell"); add_verb("sell");\
    add_action("value"); add_verb("value");\
    add_action("buy"); add_verb("buy");\
    add_action("read"); add_verb("read");\
    add_action("look"); add_verb("look");\
    add_action("west"); add_verb("west");\
    add_action("list"); add_verb("list");

TWO_EXIT("room/deep_forest1", "south",
         "players/ringer/pebble_path.c","north",
	 "Grog's magic shop",
	 "You are in Grog's magic shop. Grog's voice says from nowhere\n" +
	 "What you want? Buy, sell, list or value?\n" +
         "A magical force field covers a doorway to the west.\n" +
         "There is a sign on the northern wall.\n" +
	 "The normal exit is to the south, another exit leads north.\n",1)


sell(item) {
    int value;
    string name_of_item;
    object ob;

    if (!item)
	return 0;
    name_of_item = present(item);
    if (!name_of_item)
      name_of_item = find_item_in_player(item);
    if (!name_of_item) {
	write("No such item ("); write(item); write(") here.\n");
	return 1;
    }
    if (!call_other(name_of_item,"query_magic",0)) {
        write("Grog only buy magic things!\n");
        return 1;
    }
    value = call_other(name_of_item, "query_value", 0);
    if (!value) {
	write(item); write(" has no value.\n");
	return 1;
    }
    if (environment(name_of_item) == this_player()) {
        int weight;
	if (call_other(name_of_item, "drop", 0)) {
	    write("I can't take it from you!\n");
	    return 1;
	}
        weight = call_other(name_of_item, "query_weight", 0);
	call_other(this_player(), "add_weight", - weight);
    }
    if (value > 1000) {
	write("Grog short of cash.\n");
	value = 1000;
    }
    write("You get "); write(value*11/10); write(" gold coins.\n");
    say(call_other(this_player(), "query_name", 0) + " sells " +
	call_other(name_of_item, "short", 0) + ".\n");
    call_other(this_player(), "add_money", value*11/10);
    call_other("players/ringer/mg_sh_store", "store", name_of_item);
    return 1;
}

read(str) {
	if (str=="sign") {
            write(
"              Grog's Adventuring Tips\n\n" +
"There's no running from blink dogs!  Wimpy mode off!\n"+
"The Gorn's treasure room is hard to find, and hard to escape!\n"+
"Pure water is only for the pure of heart.\n" +
"Not all wands look like wands.\n");
            return 1;
	}
}

look(str) {
	if (str == "at sign") {
	  read("sign");
          return 1;
	}
}

value(item) {
    int value;
    string name_of_item;

    if (!item)
	return 0;
    name_of_item = present(item);
    if (!name_of_item)
      name_of_item = find_item_in_player(item);
    if (!name_of_item) {
	if (call_other("players/ringer/mg_sh_store", "value", item))
	    return 1;
	write("No such item ("); write(item); write(") here\n");
	write("or in the store.\n");
	return 1;
    }
    value = 11*call_other(name_of_item, "query_value", 0)/10;
    if (!value) {
	write(item); write(" has no value.\n");
	return 1;
    }
    write("You would get "); write(value); write(" gold coins.\n");
    return 1;
}

buy(item) {
    if (!item)
	return 0;
    call_other("players/ringer/mg_sh_store", "buy", item);
    return 1;
}

west() {
    if (call_other(this_player(), "query_level", 0) < 20) {
	write("A strong magic force stops you.\n");
	say(call_other(this_player(), "query_name", 0) +
	    " tries to go through the field, but fails.\n");
	return 1;
    }
    write("You wriggle through the force field...\n");
    call_other(this_player(), "move_player", "X#players/ringer/mg_sh_store");
    return 1;
}

list(obj) {
    call_other("players/ringer/mg_sh_store", "inventory", obj);
    return 1;
}

find_item_in_player(i)
{
    object ob;

    ob = first_inventory(this_player());
    while(ob) {
        if (call_other(ob, "id", i))
	    return ob;
	ob = next_inventory(ob);
    }
    return 0;
}



