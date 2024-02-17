#include <stdlib.h>
#include <stdio.h>

#define NBSOMMET 8
#define NBVAR 1
#define M 10
#define NBCLAUSE 2

/*                                  
        /// DEFINITION DE LA TOPOLOGIE DU GRAPHE ///


*/

int topologie[NBSOMMET][NBSOMMET]= {
    {0,1,0,0,0,0,0,0},
    {1,0,1,0,1,0,0,0},
    {0,1,0,1,0,1,1,0},
    {0,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,1},
    {0,0,1,0,1,0,0,1},
    {0,0,1,1,0,0,0,1},
    {0,0,0,0,1,1,1,0}
};

int var[NBSOMMET][NBVAR] = {
    {7},
    {8},
    {4},
    {3},
    {2},
    {7},
    {0},
    {7}
};

/*                                  
        /// DEFINITION DES MACROS ///


*/
#define NBMACRO 1

int macro_mem[NBSOMMET][NBMACRO] = {
    {0},
    {0},
    {4},
    {3},
    {2},
    {7},
    {0},
    {7}
};

int get_min(int a, int b){
    if(a<b){return a;} return b;
}

int new_clock_value(int id){
    int min = var[id][0];
        for(int i = 0 ; i< NBSOMMET ; i++){
            if (topologie[id][i]) {min = get_min(min,var[i][0]);}
        }
    return (min+1)%M;
}

int (*macro[NBCLAUSE])(int id) = {&new_clock_value};

/*                                  
        /// DEFINITION DES CLAUSES GARDEES ///


*/

int action_id[NBSOMMET] = {0,0,0,0,0,0,0,0};

int gardes_vide(int id){
    printf("new_clock_value : %d  horloge de %d : %d \n",macro_mem[id][0],id,var[id][0]);
    return (var[id][0] == macro_mem[id][0]);
}

void action_vide(int id){
    
}


int gardes_incr(int id){
    return (var[id][0] != macro_mem[id][0]);
}



void action_incr(int id){
    var[id][0] = macro_mem[id][0];
}



int (*gardes[NBCLAUSE])(int id) = {&gardes_vide,&gardes_incr};
void (*action[NBCLAUSE])(int id) = {&action_vide,&action_incr};



/*                                  
        /// DEFINITION DE LA BOUCLE D'EVALUATION  ///


*/
void eval_macro(){
    for(int i = 0 ; i<NBSOMMET; i++){
        for(int j = 0 ; j< NBMACRO; j++){
            macro_mem[i][j] = macro[j](i);
        }
    }
}

void eval_gardes(){
    for(int i=0;i<NBSOMMET;i++){
        for(int j=0; j<NBCLAUSE; j++){
            int res = (gardes[j])(i);
            if( res ){
                action_id[i] = j;
                printf("le sommet %d fera l'action %d \n",i,j);
            }
        }
    }
}

void eval_action(){
    for(int i=0;i<NBSOMMET;i++){
        action[action_id[i]](i);
        printf("le sommet %d a fait l'action %d \n",i,action_id[i]);
    }
}


void eval(int nb_cycles){ /* si on veut tourner a l'infini nb_cycles = -1*/
    int i = 0;
    while(i != nb_cycles){
        eval_macro();
        printf("debut de l'évaluation des gardes du cycles %d \n",i);
        eval_gardes();
        printf("debut des actions du cycles %d \n",i);
        eval_action();
        i++;
    }
}

int main(){

    eval(10);
    return 0;
}