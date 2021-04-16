#define MOVEME 1
object collared;
object me;
string collarname;
string myname;
int i;
int who;

short() {
      if (who == 1) {
      return "A golden leash strung around "+collarname+"'s neck";
      } else
      return "A golden leash";
}

long() { 
    write("A beautiful golden leash.\n");
    write("It enthralls you.\n");
    return 1;
}

id(str) {
    return str == "leash" || str == "golden leash";
}

leash(str) {
    
    if (!str) { return 1; }
    collared = present(lower_case(str), environment(this_player()));
    collarname = capitalize(str);
    if (!collared) {
    write(collarname+ " is not here.\n");
    return 1;
    }
    if (!living(collared)) {
    write(collarname+" is not alive!\n");
    return 1;
    }
    if (collared == this_player()) {
    write("Is this really necessary?\n");
    return 1;
    }
    me = this_player();
    myname = call_other(this_player(), "query_name");
    write("You put the leash around "+collarname+"'s neck.\n");
    set_heart_beat(1);
    who = 1;
    return 1;
}

release(str) {
    if (who != 1) {
    write("You haven't leashed anyone!\n");
    return 1;
    } else
    if (who == 1) {
    write("You release "+collarname+".\n");
    collared = 0;
    who = 0;
    set_heart_beat(0);
    return 1;
    }
}

init() {
    add_action("leash"); add_verb("leash");
    add_action("release"); add_verb("release");
}

get() { return 1; }

heart_beat() {
   i = 1;
   if((environment(collared) != environment(me)) && (i == MOVEME)) {
   tell_room(environment(collared), collarname +" bounds away after "+myname+".\n");
   tell_room(environment(me), collarname+" arrives.\n");
   move_object(collared, environment(me));
   }
}
