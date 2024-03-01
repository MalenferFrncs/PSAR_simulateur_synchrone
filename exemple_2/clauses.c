#include <stdlib.h>
#include "clauses.h"
#include "macro.h"



int gardes_vide(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (var[id][0] == macro_mem[id][0]);
}

void action_vide(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    
}


int gardes_incr(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (var[id][0] != macro_mem[id][0]);
}



void action_incr(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    var[id][0] = macro_mem[id][0];
}



int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&gardes_vide,&gardes_incr};
void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&action_vide,&action_incr};

char *nom_des_actions[NBCLAUSE] = {"rien","incr"};