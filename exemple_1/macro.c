
#include "macro.h"

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