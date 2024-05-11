#include "make_topo.h"
#include "clauses.h"
#include "compare_config.h"
#include <stdio.h>
#include <stdlib.h>

void copy(int **mem_var,int **var,int nbNode,int nbVar){
    
    for(int i=0 ; i<nbNode; i++){
        for(int j=0; j<nbVar;j++){
            
            mem_var[i][j]=var[i][j];
               /* au moins une valeur est differente on renvois faux */
        }
    }
    return ;   /* on trouve la meme config on renvoit vrais */
}

/* Fichier dans lequel ce trouve le code pour effectuer la boucle d'execution et evaluer le code de l'algorithme qu'on teste*/

void print_mem(FILE* sortie,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    fprintf(sortie,"\n");
    for(int i = 0 ; i<nbNode; i++){
        
            if(var[i][0] != ZERO_ROOT){
                fprintf(sortie,"\t\tsommet %d dist : %d,  token : %d bit : %d \n",i,var[i][0],var[i][1],var[i][2]);
            }else{
                fprintf(sortie,"\t\tsommet %d est la racine, dist : 0*,  token : %d bit : %d \n",i,var[i][1],var[i][2]);
            }
        
    }

}

/* permet d'evaluer les valeurs de toutes les macros de tout les sommets au debut du temps synchrone */
void eval_macro(FILE* sortie,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    for(int i = 0 ; i<nbNode; i++){
        for(int j = 0 ; j< NBMACRO; j++){
            macro_mem[i][j] = macro[j](i,topologie,var,macro_mem,nbNode,nbVar);}
        fprintf(sortie,"\t\tsommet %d Er : %d,  Per : %d, Take : %d \n",i,macro_mem[i][0],macro_mem[i][1],macro_mem[i][2]);
    }
}

/* permet d'evaluer les gardes de tout les sommets après l'evaluations de toutes leurs macro 
   si la garde d'indice j est passé pour le sommet i alors on stock l'indice j pour effectuer l'action d'indice j sur le noeur
   ATTENTION : si plusieurs gardes peuvent etre passé par un meme noeud on retient juste l'action avec l'indice le plus grand */
void eval_gardes(FILE* sortie,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    for(int i=0;i<nbNode;i++){
        for(int j=0; j<NBCLAUSE; j++){
            int res = (gardes[j])(i,topologie,var,nbNode,nbVar,macro_mem,action_id);
            if( res ){
                action_id[i] = j;
                /*fprintf(sortie,"\t\tle sommet : %d fera l'action : %s \n",i,nom_des_actions[j]);*/
            }
        }
    }
}

/* permet d'effectuer les actions de toutes les sommets par rapports aux gardes qu'ils ont passé sur le meme temps synchrone */
void eval_action(FILE* sortie,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    for(int i=0;i<nbNode;i++){
        action[action_id[i]](i,topologie,var,nbNode,nbVar,macro_mem,action_id,var_prec);
        fprintf(sortie,"\t\tle sommet %d a fait l'action %s \n",i,nom_des_actions[action_id[i]]);
    }
}

/* code de la boucle, s'arrete si la fonction check past renvoit vrais */
void eval(FILE* sortie,int **topologie, int **var, int nbNode, int nbVar){ /* si on veut tourner a l'infini nb_cycles = -1*/
    int i = 0;

    int **macro_mem = (int**)malloc(sizeof(int*)*nbNode);
    
    for(int i=0; i<nbNode; i++){
        
        *(macro_mem+i) = (int*)malloc(sizeof(int)*NBMACRO);
                
    }
    int finish = 0;
    config_mem *past = past_init(var,nbNode,nbVar);
    int action_id[nbNode] ;
    int **var_prec = copy_config(var,nbNode,nbVar);

    while(!finish){
        fprintf(sortie,"\n\ndebut de l'évaluation du cycles %d \n \n",i);
        fprintf(sortie,"\n\tvaleurs des macro et des memoires  \n \n");
        
        eval_macro(sortie,topologie,var,macro_mem,nbNode,nbVar);

        print_mem(sortie,topologie,var,macro_mem,nbNode,nbVar);

        /*fprintf(sortie,"\n\tdebut de l'évaluation des gardes du cycles %d \n \n",i); */
        eval_gardes(sortie,topologie,var,nbNode,nbVar,macro_mem,action_id);

        fprintf(sortie,"\n\tdebut des actions du cycles %d \n \n",i);
        eval_action(sortie,topologie,var,nbNode,nbVar,macro_mem,action_id,var_prec);
        copy(var_prec,var,nbNode,nbVar);
        i++;

        finish = check_past(var,&past,nbNode,nbVar,sortie);
    }

    fprintf(sortie,"\n\n Configuration final : \n");

    print_mem(sortie,topologie,var,macro_mem,nbNode,nbVar);

}

int main(){

    int **topo;
    int **var;
    FILE * topo_file = fopen("topo.txt","r");
    FILE * var_file = fopen("var.txt","r");
    int taille;
    int nbvar;

   
    

    taille = make_topo(&topo,topo_file);
    nbvar = make_var(&var,var_file);
   
    

    fclose(topo_file);
    fclose(var_file);

    

    FILE *sortie = fopen("example_bfs_constant.txt","w");
    if(sortie==NULL){
        printf("problème pendant l'ouverture du fichier de trace");
        return EXIT_FAILURE;
    }

    eval(sortie,topo,var,taille,nbvar);
    return 0;
}