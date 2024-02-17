#include <stdlib.h>
#include <stdio.h>

#define NBSOMMET 8
#define NBVAR 1
#define M 10



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

int (*macro[NBMACRO])(int id) = {&new_clock_value};

/*                                  
        /// DEFINITION DES CLAUSES GARDEES ///


*/
#define NBCLAUSE 2


int action_id[NBSOMMET] = {0,0,0,0,0,0,0,0};

int gardes_vide(int id){
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

char *nom_des_actions[NBCLAUSE] = {"rien","incr"};



/*                                  
        /// DEFINITION DE LA BOUCLE D'EVALUATION  ///


*/
void eval_macro(FILE* sortie){
    for(int i = 0 ; i<NBSOMMET; i++){
        for(int j = 0 ; j< NBMACRO; j++){
            macro_mem[i][j] = macro[j](i);
            fprintf(sortie,"\t\tsommet %d new_clock_value : %d,  horloge : %d \n",i,macro_mem[i][j],var[i][0]);
        }
    }
}

void eval_gardes(FILE* sortie){
    for(int i=0;i<NBSOMMET;i++){
        for(int j=0; j<NBCLAUSE; j++){
            int res = (gardes[j])(i);
            if( res ){
                action_id[i] = j;
                fprintf(sortie,"\t\tle sommet : %d fera l'action : %s \n",i,nom_des_actions[j]);
            }
        }
    }
}

void eval_action(FILE* sortie){
    for(int i=0;i<NBSOMMET;i++){
        action[action_id[i]](i);
        fprintf(sortie,"\t\tle sommet %d a fait l'action %s \n",i,nom_des_actions[action_id[i]]);
    }
}


void eval(int nb_cycles,FILE* sortie){ /* si on veut tourner a l'infini nb_cycles = -1*/
    int i = 1;
    while(i <= nb_cycles){
        fprintf(sortie,"\n\ndebut de l'évaluation du cycles %d \n \n",i);
        fprintf(sortie,"\n\tvaleurs des macro et des memoires  \n \n");
        eval_macro(sortie);
        fprintf(sortie,"\n\tdebut de l'évaluation des gardes du cycles %d \n \n",i);
        eval_gardes(sortie);
        fprintf(sortie,"\n\tdebut des actions du cycles %d \n \n",i);
        eval_action(sortie);
        i++;
    }
}

int main(){

    FILE *sortie = fopen("example_1","w");
    if(sortie==NULL){
        printf("problème pendant l'ouverture du fichier de trace");
    }

    eval(5,sortie);
    return 0;
}