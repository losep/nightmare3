//      /bin/adm/_unregister.c
//      from the Nightmare Mudlib
//      takes a site off of the list of sites needing to register
//      created by Shadowwolf@Nightmare 93????
//      rewritten for the new 3.0 security system

#include <std.h>
#include <daemons.h>
#include <security.h>

inherit DAEMON;

int cmd_unregister(string str) {
    if(!member_group(previous_object(), "SECURE")) {
    if(!member_group(previous_object(), "LAW")) return 0;
    }
    if(!str) return 0;
    if(member_array(str, (string *)BANISH_D->query_registered()) == -1) {
        write("That site is not on the list of sites needing to register.\n");
        return 1;
    }
    BANISH_D->unregister_site(str);
    log_file("watch/register", (string)previous_object()->query_name()+
      " UNREGISTERED "+str+": "+ctime(time())+"\n");
    write("Site : "+str+" is now not on the registration list.\n");
    return 1;
}


void help() {
    write("Syntax: <unregister [site]>\n\n"
      "Takes a site off the list of sites which must register their\n"
      "character before being allowed in.\n\nSee also:\n"
      "register, whoregistered, banish, unbanish, whobanished, letin,\n"
      "wholetin, unletin\n"
    );
}
