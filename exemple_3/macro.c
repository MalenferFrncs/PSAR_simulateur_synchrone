
#include "macro.h"



int token(int id,int **topo, int **var, int **macro_mem,int nbVar, int nbNode){
    
    if(id == 0){
        return(var[id][0]==var[var[id][1]][0]);
    }else{
        return(var[id][0]!=var[var[id][1]][0]);
    }
}


int (*macro[NBMACRO])(int id,int **topo, int **var, int **macro_mem,int nbVar, int nbNode) = {&token};