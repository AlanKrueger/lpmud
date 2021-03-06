/*
 * A general purpose monster. Clone this object,
 * and call local functions to configure it.
 */

/*
 * If you are going to copy this file, in the purpose of changing
 * it a little to your own need, beware:
 *
 * First try one of the following:
 *
 * 1. Do clone_object(), and then configure it. This object is specially
 *    prepared for configuration.
 *
 * 2. If you still is not pleased with that, create a new empty
 *    object, and make an inheritance of this objet on the first line.
 *    This will automatically copy all variables and functions from the
 *    original object. Then, add the functions you want to change. The
 *    original function can still be accessed with '::' prepended on the name.
 *
 * The maintainer of this LPmud might become sad with you if you fail
 * to do any of the above. Ask other wizards if you are doubtful.
 *
 * The reason of this, is that the above saves a lot of memory.
 */

#include "living.h"

/*
 * The heart beat is always started in living.h when we are attacked.
 */

string short_desc, long_desc, alias, alt_name, race;
int move_at_reset, aggressive;
object kill_ob;
status healing;		/* True if this monster is healing itself. */

object chat_head;
int chat_chance;
int chat_nr;

object a_chat_head;
int a_chat_chance;
int a_chat_nr;

object head;
object talk_ob;
string talk_func;
string talk_match;
string talk_type;
string the_text;
int have_text;


object dead_ob;
object init_ob;

int random_pick;

int spell_chance, spell_dam;
string spell_mess1, spell_mess2;
object me;
object create_room;

reset(arg)
{
    if (arg) {
	if (move_at_reset)
	    random_move();
	return;
    }
    is_npc = 1;
    enable_commands();
    me = this_object();
    create_room = environment(me);
}

random_move()
{
    int n;
    n = random(4);
    if (n == 0)
	command("west");
    else if (n == 1)
	command("east");
    else if (n == 2)
	command("south");
    else if (n == 3)
	command("north");
}

short() {
    return short_desc;
}

long() {
    write (long_desc);
}

id(str) { return str == name || str == alias || str == race || str == alt_name; }

heart_beat()
{
    int c;

    age += 1;
    /* If there is none here test_if_any_here will turn of heat_beat */
    if(!test_if_any_here()) {
	if(have_text && head) {
	    have_text = 0;
	    call_other(head, "test_match", the_text);
	} else {
	    set_heart_beat(0);
	    if (!healing)
		heal_slowly();
	    return;
	}
    }
    if (kill_ob && present(kill_ob, environment(this_object()))) {
	if (random(2) == 1)
	    return;		/* Delay attack some */
	attack_object(kill_ob);
	kill_ob = 0;
	return;
    }
    if (attacker_ob && present(attacker_ob, environment(this_object())) &&
      spell_chance > random(100)) {
	say(spell_mess1 + "\n", attacker_ob);
	tell_object(attacker_ob, spell_mess2 + "\n");
	call_other(attacker_ob, "hit_player", random(spell_dam));
    }
    attack();
    if (attacker_ob && whimpy && hit_point < max_hp/5)
	run_away();
    if(chat_head || a_chat_head){
	c = random(100);
	if(attacker_ob && a_chat_head) {
	    if(c < a_chat_chance){
		c = random(a_chat_nr);
		call_other(a_chat_head,"chat",c);
	    }
	} else {
	    if(c < chat_chance && chat_head){
		c = random(chat_nr);
		call_other(chat_head,"chat",c);
	    }
	}
    }
    if(random_pick) {
	c = random(100);
	if(c < random_pick)
	    pick_any_obj();
    }
    if(have_text && head) {
	have_text = 0;
	call_other(head, "test_match", the_text);
    }
}

can_put_and_get(str)
{
    if (!str)
	return 0;
    return 1;
}

int busy_catch_tell;

catch_tell(str) {
    string who;
    
    if (busy_catch_tell)	/* Should not happen, but does ! */
	return;
    busy_catch_tell = 1;
    if(head) {
	if(have_text) {
	    who = the_text;
	    the_text = str;
	    have_text = 1;
	    call_other(head, "test_match", the_text);
	} else {
	    the_text = str;
	    have_text = 1;
	}
    }
    busy_catch_tell = 0;
}

/*
 * Call the following functions to setup the monster.
 * Call them in the order they appear.
 */

set_name(n) {
    name = n;
    alignment = 0;		/* Neutral monster */
    cap_name = capitalize(n);
    short_desc = cap_name;
    long_desc = "You see nothing special.\n";
}

set_level(l) {
    level = l;
    weapon_class = level / 2 + 3;
    armour_class = level / 4;
    hit_point = 50 + (level - 1) * 8;	/* Same as a player */
    max_hp = hit_point;
    spell_points = max_hp;
    experience = call_other("room/adv_guild", "query_cost", l-1);
    /* This is for level 1 monsters. */
    if (experience == 0)
	experience = random(500);
}

/* Optional */
set_alias(a) { alias = a; }
/* Optional */
set_alt_name(a) { alt_name = a; }
/* Optional */
set_race(r) { race = r; }
/* optional */
set_hp(hp) { max_hp = hp; hit_point = hp; }
/* optional. Can only be lowered */
set_ep(ep) { if (ep < experience) experience = ep; }
/* optional */
set_al(al) { alignment = al; }
/* optional */
set_short(sh) { short_desc = sh; long_desc = short_desc + "\n";}
/* optional */
set_long(lo) { long_desc = lo; }
/* optional */
set_wc(wc) { weapon_class = wc; }
/* optional */
set_ac(ac) { armour_class = ac; }
/* optional */
set_move_at_reset() { move_at_reset = 1; }
/* optional
 * 0: Peaceful.
 * 1: Attack on sight.
 */
set_aggressive(a) {
    aggressive = a;
}
/*
 * Now some functions for setting up spells !
 */
/*
 * The percent chance of casting a spell.
 */
set_chance(c) {
    spell_chance = c;
}
/* Message to the victim. */
set_spell_mess1(m) {
    spell_mess1 = m;
}
set_spell_mess2(m) {
    spell_mess2 = m;
}
set_spell_dam(d) {
    spell_dam = d;
}

/* Set the frog curse. */
set_frog() {
    frog = 1;
}

/* Set the whimpy mode */
set_whimpy() {
    whimpy = 1;
}

/*
 * Force the monster to do a command. The force_us() function isn't
 * always good, because it checks the level of the caller, and this function
 * can be called by a room.
 */
init_command(cmd) {
    command(cmd);
}

/* Load chat */

set_chat_chance(c) {
    chat_chance = c;
}

remove_chat(str) { 
    chat_nr -= 1;
    chat_head = call_other(chat_head,"remove_chat",str);
}

/*
load_chat(str) {
    object old;

    chat_nr += 1;
    if(chat_head)
	old = chat_head;
    chat_head = clone_object("obj/chat");
    move_object(chat_head,this_object());
    call_other(chat_head, "load_chat", str);
    call_other(chat_head, "set_monster", this_object());
    if(old)
	call_other(chat_head, "link", old);
}
*/
/* Load attack chat */

set_a_chat_chance(c) {
    a_chat_chance = c;
}

remove_a_chat(str) { 
    a_chat_nr -= 1;
    head = call_other(a_chat_head,"remove_chat",str);
}

/*
load_a_chat(str) {
    object old;

    a_chat_nr += 1;
    if(a_chat_head)
	old = a_chat_head;
    a_chat_head = clone_object("obj/chat");
    move_object(a_chat_head,this_object());
    call_other(a_chat_head, "load_chat", str);
    call_other(a_chat_head, "set_monster", this_object());
    if(old)
	call_other(a_chat_head, "link", old);
}
*/

/* Catch the talk */

set_object(ob) { 
    talk_ob = ob; 
}

set_function(func) { 
    talk_func = func; 
}

set_type(type) { 
    talk_type = type; 
}

/*
set_match(match) {
    object old;

    talk_match = match; 
    if(head)
	old = head;
    head = clone_object("obj/catch_talk");
    move_object(head,this_object());
    call_other(head, "set_object", talk_ob);
    call_other(head, "set_function", talk_func);
    call_other(head, "set_match", talk_match);
    call_other(head, "set_type", talk_type);
    if(old)
	call_other(head, "link", old);
}
*/

remove_match(match) { 
    head = call_other(head,"remove_match",match);
}

set_dead_ob(ob)
{
    dead_ob = ob;
}

second_life()
{
    /* We have died remove chat and catch_talk */
    if(head)
	call_other(head,"collaps");
    if(chat_head)
	call_other(chat_head,"collaps");
    if(a_chat_head)
	call_other(a_chat_head,"collaps");
    if(dead_ob)
	return call_other(dead_ob,"monster_died",this_object());
}

set_random_pick(r)
{
    random_pick = r;
}

pick_any_obj() {
    object ob;
    int weight;

    ob = first_inventory(environment(this_object()));
    while(ob) {
	if (call_other(ob, "get", 0) && call_other(ob, "short")) {
	    weight = call_other(ob, "query_weight", 0);
	    if (!add_weight(weight)) {
		say(cap_name + " tries to take " + call_other(ob, "short", 0) +
		    " but fails.\n");
		return;
	    }
	    move_object(ob, this_object());
	    say(cap_name + " takes " + call_other(ob, "short", 0) + ".\n");
	    if (call_other(ob, "weapon_class", 0))
		call_other(ob, "wield", call_other(ob,"query_name"));
	    else if (call_other(ob, "armour_class", 0))
		call_other(ob, "wear", call_other(ob,"query_name"));
	    return;
	}
	ob = next_inventory(ob);
    }
}

set_init_ob(ob)
{
    init_ob = ob;
}

init() {

    create_room = environment(me);
    if(this_player() == me)
	return;
    if(init_ob)
	if(call_other(init_ob,"monster_init",this_object()))
	    return;
    if (attacker_ob) {
	set_heart_beat(1); /* Turn on heart beat */
    }
    if(this_player() && !call_other(this_player(),"query_npc")) {
	set_heart_beat(1);
	if (aggressive == 1)
	    kill_ob = this_player();
    }
}

query_create_room() { return create_room; }

query_race() { return race; }

/*
 * The monster will heal itself slowly.
 */
heal_slowly() {
    hit_point += 120 / (INTERVAL_BETWEEN_HEALING * 2);
    if (hit_point > max_hp)
	hit_point = max_hp;
    spell_points += 120 / (INTERVAL_BETWEEN_HEALING * 2);
    if (spell_points > max_hp)
	spell_points = max_hp;
    healing = 1;
    if (hit_point < max_hp || spell_points < max_hp)
	call_out("heal_slowly", 120);
    else
	healing = 0;
}
