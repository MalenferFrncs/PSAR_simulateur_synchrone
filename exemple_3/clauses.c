#include <stdlib.h>
#include "topologie.h"
#include "clauses.h"
#include "macro.h"

int action_id[NBSOMMET] = {0,0,0,0,0,0,0,0};

int gardes_vide(int id){
    return (!macro_mem[id][0]);
}

void action_vide(int id){
    
}


int gardes_T(int id){
    return (macro_mem[id][0]);
}



void action_T(int id){
    if(id==0){
        var[id][0] = (var[id][0]+1)%K ;
    }else{
        var[id][0] = var[var[id][1]][0];
    }
}



int (*gardes[NBCLAUSE])(int id) = {&gardes_vide,&gardes_T};
void (*action[NBCLAUSE])(int id) = {&action_vide,&action_T};

char *nom_des_actions[NBCLAUSE] = {"rien","T"};