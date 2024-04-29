#include <stdlib.h>

#include "clauses.h"


/* macro */

int token(int id,int **topo, int **var, int **macro_mem,int nbVar, int nbNode){
    
    if(id == 0){
        return(var[id][0]==var[var[id][1]][0]);
    }else{
        return(var[id][0]!=var[var[id][1]][0]);
    }
}


int (*macro[NBMACRO])(int id,int **topo, int **var, int **macro_mem,int nbVar, int nbNode) = {&token};


/* clauses */

int gardes_vide(int id, int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (!macro_mem[id][0]);
}

void action_vide(int id, int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    
}


int gardes_T(int id, int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (macro_mem[id][0]);
}



void action_T(int id, int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if(id==0){
        var[id][0] = (var[id][0]+1)%K ;
    }else{
        var[id][0] = var[var[id][1]][0];
    }
}



int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&gardes_vide,&gardes_T};
void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&action_vide,&action_T};

char *nom_des_actions[NBCLAUSE] = {"rien","T"};