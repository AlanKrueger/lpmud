# 1 "room/elevator.c"
# 1 "room/std.h"







































































































































































# 2 "room/elevator.c"









int level;
int door_is_open;
int time_to_close_door;
int dest;		
int moving_time;	
int delay_to_reset;	

init() {
    add_action("press", "press");
    add_action("press", "push");
    add_action("open_door", "open");
    add_action("close_door", "close");
    add_action("go_east", "east");
}

short() {
    return "elevator";
}

reset(arg) {
    door_is_open = 0;
    if (arg)
	return;
    set_light(1);
    level = 2;
    dest = 2;
    moving_time = 0;
}





query_door() { return !door_is_open; }

long() {
    write("You are in the elevator. On the wall are three buttons,\n");
    write("numbered 1 to 3.\n");
    if (door_is_open)
	write("There is an open door to the east.\n");
    if (!door_is_open)
	write("There is a closed door to the east.\n");
}

press(button) {
    string b;
    if (!button)
	return 0;
    if (door_is_open) {
	write("Nothing happens.\n");
	return 1;
    }
    if (sscanf(button, "button %s", b) != 1)
	b = button;
    if (moving_time > 0) {
	write("The elevator is still moving.\n");
	return 1;
    }
    if (b == "1" || b == "one")
	dest = 1;
    if (b == "2" || b == "two")
	dest = 2;
    if (b == "3" || b == "three")
	dest = 3;
    if (dest == level) {
	write("You are alread at level " + dest + ".\n");
	return 1;
    }
    if (dest > level) {
	moving_time = dest - level;
	write("The elevator jerks upward.\n");
	say("The elevator jerks upward.\n");
    }
    if (level > dest) {
	moving_time = level - dest;
	write("The elevator starts moving downward.\n");
	say("The elevator starts moving downward.\n");
    }
    if (dest == 1 || level == 1)
	moving_time += 10;
    moving_time += 1;
    set_heart_beat(1);
    return 1;
}

heart_beat() {
    if (time_to_close_door > 0) {
	time_to_close_door -= 1;
	if (time_to_close_door == 0) {
	    say("The door swings shut.\n");
	    door_is_open = 0;
	}
    }
    if (moving_time <= 0)
	return;
    moving_time -= 1;
    if (moving_time > 0) {
	say("The elevator continues...\n");
	return;
    }
    say("The elevator slows down and stops\n");
    set_heart_beat(0);
    level = dest;
    if (level == 2)
	call_other("room/church", "elevator_arrives", 0);
    if (level == 1)
	call_other("room/wiz_hall", "elevator_arrives", 0);
}

open_door(str)
{
    if (str != "door")
	return 0;
    if (door_is_open) {
	write("It is already open!\n");
	return 1;
    }
    if (moving_time > 0) {
	write("The door is stuck.\n");
	return 1;
    }
    door_is_open = 1;
    time_to_close_door = 3;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) + " opened the door.\n");
    return 1;
}

close_door(str)
{
    if (str != "door")
	return 0;
    if (!door_is_open) {
	write("It is closed!\n");
	return 1;
    }
    door_is_open = 0;
    time_to_close_door = 0;
    write("Ok.\n");
    say(call_other(this_player(), "query_name", 0) + " closed the door.\n");
    return 1;
}

go_east() {
    if (moving_time > 0) {
	write("You can't go anywhere when the elevator is moving.\n");
	return 1;
    }
    if (!door_is_open) {
	write("The door is closed.\n");
	return 1;
    }
    if (level == 2)
	call_other(this_player(), "move_player", "east#room/church");
    if (level == 1)
	call_other(this_player(), "move_player", "east#room/wiz_hall");
    if (level == 3)
	call_other(this_player(), "move_player", "east#room/attic");
    return 1;
}

query_level() { return level; }




call_elevator(button) {
    if (door_is_open)
	return 0;
    if (moving_time > 0)
	return 0;
    dest = button;
    if (dest == level)
	return 0;
    write("A little white lamp beside the button lights up.\n");
    say("A little white lamp beside the button lights up.\n");
    if (dest > level)
	moving_time = dest - level;
    if (level > dest)
	moving_time = level - dest;
    if (dest == 1 || level == 1)
	moving_time += 10;
    moving_time += 1;
    set_heart_beat(1);
    return 1;
}

id(str) {
    return str == "door" || str == "button" || str == "buttons";
}




can_put_and_get()
{
    return 0;
}



is_moving() { 
    if (level == dest )
	
	return 0;
    if(level > dest)
	
	return 1;
    
    return 2;
}

query_drop_castle() {
    return 1;
}
