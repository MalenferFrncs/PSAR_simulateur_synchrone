#include <stdlib.h>
#include "topologie.h"
#include "clauses.h"
#include "macro.h"

int action_id[NBSOMMET] = {0,0,0,0,0,0,0,0};

int gardes_vide(int id){
    return (var[id][0] == new_clock_value(id));
}

void action_vide(int id){
}


int gardes_incr(int id){
    return (var[id][0] != new_clock_value(id));
}



void action_incr(int id){
    var[id][0] = new_clock_value(id);
}



int (*gardes[NBCLAUSE])(int id) = {&gardes_vide,&gardes_incr};
void (*action[NBCLAUSE])(int id) = {&action_vide,&action_incr};
