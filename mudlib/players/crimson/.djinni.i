# 1 "players/crimson/.djinni.c" 
# 1 "/home/einstein/mud/lpmud/mudlib/room/std.h" 1







































































































































































# 2 "players/crimson/.djinni.c" 2
# 1 "/home/einstein/mud/lpmud/mudlib/obj/handshake.h" 1



string handshake_data;
int handshake;









get_handshake(confirm) {
    if (confirm == handshake && handshake) {
        handshake = 0;
	return handshake_data;
    } else {
        return 0;
    }
}
# 3 "players/crimson/.djinni.c" 2
int i, charges;
int is_npc;
int magic;
object targetloc;
string pointo;

id(str) { return str == "aladin's lamp" || str == "magic lamp" || str == "magic lamp" || str == "lamp"; }

reset(arg) {
    if (!arg) charges= 1;
    magic = 1;
}

long() {
    write("This lamp looks like it is made of a rare metal. It's appearance is very\n");
    write("dingy. Oddly, it still feels warm to the touch.\n");
}

short() {
     return "A beat up old lamp";
}

query_value()
{
    return 10000;
}

query_weight() {
     return 1;
}

read(str) {
    if (!id(str)) return 0;
    write("You cannot comprehend the runes on the lamp.\n");
    return 1;
}

no_find(str) {
    if (str == "lamp" || "old lamp") {
    write("What?\n");
    return 1;
    }
}

light(str) {
    if (!id(str)) return 0;
    write("OUCH!, would you really burn me, my master?\n");
    return 1;
}

init() {
    add_action("rub"); add_verb("rub");
    add_action("set"); add_verb("battle");
    add_action("stat"); add_verb("stat");
    add_action("read"); add_verb("read");
    add_action("no_find"); add_verb("origin");
    add_action("light"); add_verb("light");
}

rub(str) {
    object otherplayer;
    object djinni;
    object thisplayer;

    if (!str) { return 1; }
    otherplayer = pointo;
    if (!otherplayer) {
    write("What is it you want me to battle, my master?\n");
    return 1;
    }
    if (i != 1) {
    return 1;
    }
            targetloc = environment(otherplayer);
            thisplayer = this_player();
                write("You summon the djinni to do your bidding.\n");
                say(call_other(this_player(), "query_name") + " rubs a small dented lamp.\n");
                tell_room(targetloc, "A djinni solidifies from a blue vapor.\n");
                djinni = clone_object("obj/monster"); {
                call_other(djinni, "set_name", "djinni");
                call_other(djinni, "set_alias", "djinni");
                call_other(djinni, "set_short", "A handsome djinni");
                call_other(djinni, "set_level", 18);
                call_other(djinni, "set_long", "Before you is a dark and suave looking figure of a man.\n" +
                    "He has black wavey hair and an upturned mustache. A cloud\n" +
                    "of sapphire blue smoke encircles his lower midriff.\n");
                call_other(djinni, "set_al", 500);
                call_other(djinni, "set_wc", 35);
                call_other(djinni, "set_ac", 11);
                call_other(djinni, "set_can_kill", 1);
                call_other(djinni, "set_aggressive", 0);
                move_object(djinni, targetloc);
                call_other(djinni, "attack_object", otherplayer);
                }
                if (charges == 1) {
                    destruct(this_object());
                    tell_object(thisplayer, "You watch as the djinni snatches his lamp.\n");
                }
                if (is_npc)
                return 1;
}

set(arg) {

    if (!arg) {
        return 0;
    }
    else {

         pointo = find_living(arg);
        write("The djinni understands.\n");
        i = 1;
    }
   return 1;
}

get() {
    return 1;
}

stat(arg) {
    if (!arg || arg != "lamp" ||
        call_other(this_player(),"query_level",0)<20) return 0;
    write("Lamp stats:\ncharges: "+charges+"\nsetting: "+pointo+"\n");
    return 1;
}

query_magic() { return magic; }
