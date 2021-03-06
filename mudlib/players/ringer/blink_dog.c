/*
 * A blink dog.  Clone this object,
 * and call local functions to configure it.
 */
#include "../../obj/living.h"

/*
 * The heart beat is always started in living.h when we are attacked.
 */

string short_desc, long_desc, alias;
int move_at_reset, aggressive;
object kill_ob;

int spell_chance, spell_dam;
string spell_mess1, spell_mess2;

valid_attack(ob) { return !call_other(ob, "query_npc"); }

reset(arg)
{
    if (arg) {
	if (move_at_reset)
	    random_move();
	return;
    }
    is_npc = 1;
    enable_commands();
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

id(str) { return str == name || str == alias; }

heart_beat()
{
    age += 1;
/*    if (kill_ob && !present(kill_ob)) */
/*      teleport(environment(kill_ob)); */
    if (attacker_ob && !present(attacker_ob,environment(this_object()))) {
      teleport(environment(attacker_ob)); 
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
	say(spell_mess1 + "\n");
	tell_object(attacker_ob, spell_mess2 + "\n");
	call_other(attacker_ob, "hit_player", random(spell_dam));
    }

    attack();
    if (attacker_ob && whimpy && hit_point < max_hp/5)
	run_away();
}


teleport(ob) {
    say(short() + " disappears!\n");
    move_object(this_object(),ob);
    say(short() + " appears!\n");
}


can_put_and_get(str)
{
    if (!str)
	return 0;
    return 1;
}

catch_tell(str) {
    string who;
    object ob;

    if (!str) return 0;
    if (attacker_ob)
	return;
    if (aggressive == 1 && sscanf(str, "%s arrives", who) == 1) {
	kill_ob = this_player();
	set_heart_beat(1);
    }
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

/* Optional */
set_alias(a) {
    alias = a;
}

set_level(l) {
    level = l;
    weapon_class = WEAPON_CLASS_OF_HANDS;
    armor_class = 0;
    hit_point = 50 + (level - 1) * 8;	/* Same as a player */
    max_hp = hit_point;
    experience = call_other("room/adv_guild", "query_cost", l-1);
}

/* optional */
set_hp(hp) { max_hp = hp; hit_point = hp; }
/* optional */
set_ep(ep) { experience = ep; }
/* optional */
set_al(al) { alignment = al; }
/* optional */
set_short(sh) { short_desc = sh; long_desc = short_desc + "\n";}
/* optional */
set_long(lo) { long_desc = lo; }
/* optional */
set_wc(wc) { weapon_class = wc; }
/* optional */
set_ac(ac) { armor_class = ac; }
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
