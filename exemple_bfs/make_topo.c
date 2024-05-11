#include <stdlib.h>
#include <stdio.h>
#include "make_topo.h"

int make_topo(int ***topo, FILE* topo_file){
    int taille;
    int buf;

    
    fscanf(topo_file,"%d\n",&taille);

    
   

    *topo = (int**)malloc(sizeof(int*)*taille);
    if(*topo==NULL){
         printf("PB allocation topo");
        return EXIT_FAILURE;
    }
    
    for(int i=0; i<taille; i++){
        
        *(*topo+i) = (int*)malloc(sizeof(int)*taille);

        if(*(*topo+i)==NULL){
         printf("PB allocation topo");
        return EXIT_FAILURE;
    }

        for(int j=0; j<taille-1; j++){
            fscanf(topo_file,"%d ",&buf);
            (*topo)[i][j]=buf;
        }
        
        fscanf(topo_file,"%d\n",&((*topo)[i][(taille-1)]));
        
        
    }

    return taille;
}

int make_var(int ***var, FILE* var_file){
    int nbvar;
    int taille;
    fscanf(var_file,"%d\n%d",&taille,&nbvar);
    
    *var = (int**)malloc(sizeof(int*)*taille);
    
    for(int i=0;i<taille;i++){
        int id;
        int buf;
        fscanf(var_file,"%d;",&id);
        *(*var+id) = (int*)malloc(sizeof(int)*nbvar);

        for(int j =0 ; j<nbvar-1 ; j++){
            fscanf(var_file,"%d;",&buf);
            (*var)[id][j] = buf;
        }
        fscanf(var_file,"%d\n",&((*var)[id][nbvar-1]));
    }

    return nbvar;
}

