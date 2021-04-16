# 1 "room/eastroad1.c"
# 1 "room/room.h"
inherit "room/room";
























# 2 "room/eastroad1.c"
reset(arg) { if (!arg) { set_light( 1); short_desc =  "East road"; long_desc =  "East road runs north-south.\n"; dest_dir = ({ "room/eastroad2", "north",           "room/vill_shore", "south" }); }  }
# 7 "room/eastroad1.c"

