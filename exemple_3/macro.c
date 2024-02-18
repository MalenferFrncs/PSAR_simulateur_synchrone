#include "topologie.h"
#include "macro.h"



int token(int id){
    
    if(id == 0){
        return(var[id][0]==var[var[id][1]][0]);
    }else{
        return(var[id][0]!=var[var[id][1]][0]);
    }
}

int macro_mem[NBSOMMET][NBMACRO] = {
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
    {0}
};

int (*macro[NBMACRO])(int id) = {&token};