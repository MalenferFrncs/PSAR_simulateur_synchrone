#include <stdlib.h>

#include "clauses.h"
/* fichier dans lequel on ecrit le code correspondant a l'algorithme qu'on veut tester s*/


/* code des macros */

int get_min(int a, int b){
    if(a<b){return a;} return b;
}

int new_clock_value(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    int min = var[id][0];
        for(int i = 0 ; i< nbNode ; i++){
            if (topologie[id][i]) {min = get_min(min,var[i][0]);}
        }
    return (min+1)%M;
}

int (*macro[NBMACRO])(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar) = {&new_clock_value};

/* code qui correspond aux gardes et aux actions de l'algorithme*/


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


/* structures qui stock l'adresse du code des gardes et des actions (tableau de pointeur de fonction)*/
int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&gardes_vide,&gardes_incr};
void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&action_vide,&action_incr};

char *nom_des_actions[NBCLAUSE] = {"rien","incr"};