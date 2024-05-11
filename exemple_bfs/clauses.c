#include <stdlib.h>
#include <stdio.h>

#include "clauses.h"
/* fichier dans lequel on ecrit le code correspondant a l'algorithme qu'on veut tester s*/

int in_parent(int dist,int dist_voisin){
    if(dist_voisin==ZERO_ROOT){dist_voisin=0;}
    if(dist_voisin == ((dist-1)%3)){
        return 1;
    }
    return 0;
}

int in_child(int dist,int dist_voisin){
    if(dist_voisin==ZERO_ROOT){dist_voisin=0;}
    if((dist_voisin == ((dist+1)%3))&& dist != 0){
        return 1;
    }
    return 0;
}

int in_NTok(int token){
    if(token==TRUE){
        return 1;
    }
    return 0;
}


/* code des macros */

int Er(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    int first_neighbor=1,b_first;
    for(int i=0; i<nbNode; i++){
        if(topologie[id][i]==1){  /* voisin */
            if(in_child(var[id][0],var[i][0])){ /* child */
             if(first_neighbor){
                first_neighbor =0;
                b_first = var[i][2];      /*si on est le 1er child on ne peu comparer notre bit a personne */
             } else {
                if(b_first != var[i][2]) {return 1;} /* sinon on compare au 1er noeud pour voir si ils sont coherent*/
             }                                      /*si on a 2 bit different on est vrais (en erreur)*/
            
        

            }
        }
    }
    return 0; /* si tout les sommet de child sont coherent on est faux*/
}


int Per(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    for(int i=0; i<nbNode; i++){
        if(topologie[id][i]==1){  /* voisin */
            if(in_parent(var[id][0],var[i][0] || var[i][0]==ZERO_ROOT)){ /* child */
             
                if(var[i][1]==ER){return 1;} /* si un sommet de parent a token = er on est vrais*/
        

            }
        }
    }
    return 0; /* si tout les sommet de parent sont coherent on est faux*/
}

int Take(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar){
    int first_neighbor=1,d_first;
    for(int i=0; i<nbNode; i++){
        if(topologie[id][i]==1){  /* voisin */
            if(in_NTok(var[i][1])){ /* voisin avec un token */
             if(first_neighbor){
                first_neighbor = 0;
                d_first = var[i][0];      /*si on est le 1er voisin on ne peu comparer notre dist a personne */
             } else {
                if(d_first != var[i][0]) { return 0;} /* sinon on compare au 1er noeud pour voir si ils sont coherent*/
             }
            
             if(var[i][2]==0){return 0;} /* si un bit d'un sommet dans NTok est different de 1 on est faux*/

            }
        }
    }
    if(first_neighbor){ return 0;}
    
    return 1; /* si tout les sommet de NTok sont coherent on est vrais */
}

int (*macro[NBMACRO])(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar) = {&Er,&Per,&Take};

/* code qui correspond aux gardes et aux actions de l'algorithme*/

int garde_rien(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (1);
}

void action_rien(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    
}

int gardes_Er(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (macro_mem[id][0] && var[id][0]!=ZERO_ROOT );
}

void action_Er(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=ER;
}

int gardes_Correct(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if( (!(macro_mem[id][0])) && var[id][1]==FALSE && macro_mem[id][1]  && var[id][0]!=ZERO_ROOT ){
        return 1;
    }
    return 0;
}

void action_Correct(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    for(int i=0; i<nbNode; i++){
        if(topologie[id][i]==1){  /* voisin */
            if(var_prec[i][0]=ZERO_ROOT){ /* voisin avec la racine */
                var[id][0] = 1;
                break;
            }
        }
    }
    var[id][1]=FALSE;
    var[id][2] = 0;
}

int gardes_tok(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if( (!(macro_mem[id][0])) && var[id][1]==FALSE && !macro_mem[id][1] && macro_mem[id][2] && var[id][0]!=ZERO_ROOT ){
        return 1;
    }
    return 0;
}

void action_tok(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=TRUE;
    
    for(int i=0; i<nbNode; i++){
        if(topologie[id][i]==1){  /* voisin */
        
            if(in_NTok(var_prec[i][1])){ /* voisin avec un token */
                int dist;
                if(var_prec[i][0]==ZERO_ROOT){dist = 0 ;}else{dist = var_prec[i][0];}
                
                var[id][0] = (dist+1)%3;
                return;
            }
        }
    }
}

int gardes_update(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if( (!(macro_mem[id][0])) && var[id][1]==TRUE && var[id][0]!=ZERO_ROOT  ){
        return 1;
    }
    return 0;
}

void action_update(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=WAIT;
    var[id][2] = (var[id][2]+1)%2;
}

int gardes_ready(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if( (!(macro_mem[id][0])) && (var[id][1]==ER || var[id][1]==WAIT ) && var[id][0]!=ZERO_ROOT ){
        return 1;
    }
    return 0;
}

void action_ready(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=FALSE;
}

int gardes_Clean(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    if(var[id][0]==ZERO_ROOT && var[id][1]==TRUE){
        int first_neighbor=1,b_first;
        for(int i=0; i<nbNode; i++){
            if(topologie[id][i]==1){  /* voisin */
                if(first_neighbor){
                    first_neighbor = 0;
                    b_first = var[i][2];      /*si on est le 1er voisin on ne peu comparer notre dist a personne */
                } else {
                    if(b_first != var[i][2]) {return 1;} 
                }
                if(var[i][0]!=1){return 1;}
            }
        }
    }
    return 0;
}

void action_Clean(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=ER;
}

int gardes_Go(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id){
    return (var[id][1]==ER && var[id][0]==ZERO_ROOT);
}

void action_Go(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec){
    var[id][1]=TRUE;
}

/* structures qui stock l'adresse du code des gardes et des actions (tableau de pointeur de fonction)*/
int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) = {&garde_rien,&gardes_Er,&gardes_Correct,&gardes_tok,&gardes_update,&gardes_ready,&gardes_Clean,&gardes_Go};
void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec) = {&action_rien,&action_Er,&action_Correct,&action_tok,&action_update,&action_ready,&action_Clean,&action_Go};

char *nom_des_actions[NBCLAUSE] = {"rien","Er","Correct","Tok","update","ready","clean","go"};