# 1 "room/south/sforst2.c"
reset(started)
{
    if (!started)
	set_light(1);
}

init()
{
    add_action("north"); add_verb("north");
    add_action("south"); add_verb("south");
    add_action("west");  add_verb("west");
}

short()
{
    return "A dimly lit forest";
}

long()
{
    write("You are in part of a dimly lit forest.\n" +
	  "Trails lead north, south and west\n");
}

north()
{
    call_other(this_player(), "move_player", "north#room/south/sforst1");
    return 1;
}

south()
{
    call_other(this_player(), "move_player", "south#room/south/sforst3");
    return 1;
}

west()
{
    call_other(this_player(), "move_player", "west#room/south/sforst6");
    return 1;
}
