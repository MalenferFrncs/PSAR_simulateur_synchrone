#include <stdio.h>
#include <stdlib.h>

/* fichier dans lequel ce trouve le code qui permet de tester les configurations passé*/


/* structure chainé dans laquel on stock les configurations passé du système*/
struct _past_config{
    int ** config;
    struct _past_config *next;
    int index;
};

typedef struct _past_config config_mem;

/* fonction qui compare 2 configurations (egalité de matrices) */

int compare(int **current_config,int **past_config,int nbNode,int nbVar){
    
    for(int i=0 ; i<nbNode; i++){
        for(int j=0; j<nbVar;j++){
            
            if(current_config[i][j]!=past_config[i][j])
                return 0;   /* au moins une valeur est differente on renvois faux */
        }
    }
    return 1;   /* on trouve la meme config on renvoit vrais */
}

/* crée une zone memoire et copie une matrice dedans */

int **copy_config(int **src, int nbNode, int nbVar){ /* renvoit l'adresse de la nouvelle matrice*/
    
    int **dest;
    
    
    dest = (int**)malloc(sizeof(int*)*nbNode);
    
    for(int i=0;i<nbNode;i++){
        
        
        *(dest+i) = (int*)malloc(sizeof(int)*nbVar);

        for(int j =0 ; j<nbVar ; j++){
            
            dest[i][j] = src[i][j];
        }

       
    }

    
    
    return dest;
    
}


/* ajoute une matrice copié sur celle de la configuration curent_config en tete de notre structure */

config_mem *new_past(int ** curent_config, config_mem *past,int nbNode,int nbVar){
    
    config_mem* new_mem = (config_mem*)malloc(sizeof(config_mem));
    new_mem->next = past;
    new_mem->config = copy_config(curent_config,nbNode,nbVar);
    new_mem->index = (past->index) +1;
    
    return new_mem;
}

/* initialise notre structure */
config_mem *past_init(int** curent_config,int nbNode,int nbVar){
    config_mem* new_mem = (config_mem*)malloc(sizeof(config_mem));
    new_mem->next = NULL;
    new_mem->config = copy_config(curent_config,nbNode,nbVar);
    new_mem->index = 0;
    
    return new_mem;
}

/* compare current_config avec toutes les configurations passé pour voir si on l'a deja vue*/
int check_past(int ** curent_config, config_mem **past, int nbNode,int nbVar,FILE* sortie){
    int found = 0;
    config_mem *test = *past;
    
    

    while(test != NULL && !found){  /* on arrete le parcour si on atteint la fin ou si on trouve une config identique */
        
        found = compare(curent_config, test->config, nbNode,nbVar);
        test = test->next;
        
    }

    
    if(!found){
        *past = new_past(curent_config,*past,nbNode,nbVar);
    }else{
        fprintf(sortie,"\n fin de la simulation, on a deja vu la prochaine configuration a l'indice %d\n",test->index+1);
    }

    return found;

}