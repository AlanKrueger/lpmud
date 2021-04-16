string rope;
reset(arg)
{
    if (!arg)
	set_light(0);
}

init()
{
    add_action("up"); add_verb("up");
    add_action("up"); add_verb("climb");
    add_action("down"); add_verb("down");
    add_action("down"); add_verb("climb");
    add_action("swing"); add_verb("swing");
}

up()
{
    call_other(this_player(), "move_player", "up the rope#players/crimson/greeting");
    return 1;
}

swing() {
     tell_object(this_player(), "Whoa, whoa, WHOA!\n");
     tell_object(this_player(), "You're not going to make it.\n");
     tell_object(this_player(), "You're not going to make it!\n");
     call_other(this_player(), "move_player", "swinging wildly on the rope#players/crimson/underworld3");
     return 1;
}

long()
{
    write("Zowy! That was close! You stop for a moment to slow down your now\n");
    write("swiftly beating heart. Hesitatingly, you continue your travels.\n");
}

short() {
    return "Under the greeting hall";
}

realm() { return "NT"; }
down() {
    call_other(this_player(), "move_player", "down the rope#players/crimson/underworld4");
    return 1;
}
