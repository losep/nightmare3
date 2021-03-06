/*    /daemon/estates.c
 *    from Nightmare IV
 *    a daemon for handling Estate events
 *    created by Descartes of Borg 940702
 */

#include <std.h>
#include <security.h>
#include <objects.h>
#include <save.h>
#include "estates.h"

inherit DAEMON;

private mapping __Estates;

void create() {
    daemon::create();
    __Estates = ([]);
    set_no_clean(1);
    if(file_exists(SAVE_ESTATES+__SAVE_EXTENSION__)) restore_object(SAVE_ESTATES);
    preload_estates();
}

private void preload_estates() {
    object ob;
    string *who;
    string desc;
    int i, j;

    i = sizeof(who = keys(__Estates));
    while(i--) {
        if((j = sizeof(__Estates[who[i]])) > 1)
          desc = "an estate of "+who[i];
        else desc = possessive_noun(who[i])+" estate";
        while(j--) {
            ob = new(OB_ESTATE);
            ob->set_short(desc);
            ob->set_long(__Estates[who[i]][j][2]);
            ob->set_exit(__Estates[who[i]][j][0]);
            __Estates[who[i]][j][1]->set_no_clean(1);
            ob->move(__Estates[who[i]][j][1]);
        }
    }
}

void add_estate(string who, string sortie, string where, string long) {
    object ob;

    if(base_name(previous_object()) != OB_DEED) return;
    if(!__Estates[who]) __Estates[who] = ({ ({ sortie, where, long }) });
    else __Estates[who] += ({ ({ sortie, where, long }) });
    ob = new(OB_ESTATE);
    ob->set_short(possessive_noun(who)+" estate");
    ob->set_long(long);
    ob->set_exit(sortie);
    where->set_no_clean(1);
    ob->move(where);
    ob->reinitiate();
    save_object(SAVE_ESTATES);
}
