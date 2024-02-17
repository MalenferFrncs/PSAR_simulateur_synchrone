#include "topologie.h"
#include "clauses.h"

int actions_tick[NBSOMMET][NBCLAUSE];

void eval_gardes(){
    for(int i=0;i<NBSOMMET;i++){
        for(int j=0; j<NBCLAUSE; j++){
            if( (gardes[j])(i) ){
                action_id[i] = j;
            }
        }
    }
}

void eval_action(){
    for(int i=0;i<NBSOMMET;i++){
        action[action_id[i]](i);
    }
}


void eval(){
    while(1){
        eval_gardes();
        eval_action();

    }
}

int main(){
    eval();
    return 0;
}