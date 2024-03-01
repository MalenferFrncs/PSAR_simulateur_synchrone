#include <stdio.h>
#include <stdlib.h>
struct _past_config{
    int ** config;
    struct _past_config *next;
};

typedef struct _past_config config_mem;

int compare(int **current_config,int **past_config,int nbNode,int nbVar){
    
    for(int i=0 ; i<nbNode; i++){
        for(int j=0; j<nbVar;j++){
            
            if(current_config[i][j]!=past_config[i][j])
                return 0;   /* au moins une valeur est differente on renvois faux */
        }
    }
    return 1;   /* on trouve la meme config on renvoit vrais */
}

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




config_mem *new_past(int ** curent_config, config_mem *past,int nbNode,int nbVar){
    
    config_mem* new_mem = (config_mem*)malloc(sizeof(config_mem));
    new_mem->next = past;
    new_mem->config = copy_config(curent_config,nbNode,nbVar);
    
    return new_mem;
}

config_mem *past_init(int** curent_config,int nbNode,int nbVar){
    config_mem* new_mem = (config_mem*)malloc(sizeof(config_mem));
    new_mem->next = NULL;
    new_mem->config = copy_config(curent_config,nbNode,nbVar);
    
    return new_mem;
}

int check_past(int ** curent_config, config_mem **past, int nbNode,int nbVar){
    int found = 0;
    config_mem *test = *past;

    

    while(test != NULL && !found){  /* on arrete le parcour si on atteint la fin ou si on trouve une config identique */
        
        found = compare(curent_config, test->config, nbNode,nbVar);
        
        test = test->next;
    }

    
    if(!found){
        *past = new_past(curent_config,*past,nbNode,nbVar);
    }

    return found;

}