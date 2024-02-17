#include "topologie.h"
#include "macro.h"

int get_min(int a, int b){
    a<b ? a : b ;
}

int new_clock_value(int id){
    int min = var[id][0];
        for(int i = 0 ; i< NBSOMMET ; i++){
            if (topologie[id][i]) {min = get_min(min,var[i][0]);}
        }
    return (min+1)%M;
}
