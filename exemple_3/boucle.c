#include "topologie.h"
#include "clauses.h"
#include "macro.h"
#include <stdio.h>

void eval_macro(FILE* sortie){
    for(int i = 0 ; i<NBSOMMET; i++){
        fprintf(sortie,"\t\tsommet %d",i);
        for(int j = 0 ; j< NBMACRO; j++){
            macro_mem[i][j] = macro[j](i);
            fprintf(sortie," Token : %d,  v : %d \n",macro_mem[i][j],var[i][0]);
        }
    }
}

void eval_gardes(FILE* sortie){
    for(int i=0;i<NBSOMMET;i++){
        for(int j=0; j<NBCLAUSE; j++){
            int res = (gardes[j])(i);
            if( res ){
                action_id[i] = j;
                /* fprintf(sortie,"\t\tle sommet : %d fera l'action : %s \n",i,nom_des_actions[j]); */
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
        /* fprintf(sortie,"\n\tdebut de l'évaluation des gardes du cycles %d \n \n",i); */
        eval_gardes(sortie);
        fprintf(sortie,"\n\tdebut des actions du cycles %d \n \n",i);
        eval_action(sortie);
        i++;
    }
}

int main(){

    FILE *sortie = fopen("example_3_Token_ring.txt","w");
    if(sortie==NULL){
        printf("problème pendant l'ouverture du fichier de trace");
    }

    eval(20,sortie);
    return 0;
}