#ifndef CLAUSES_H
#define CLAUSES_H

#define NBMACRO 1



extern int (*macro[NBMACRO])(int id,int **topo, int **var, int **macro_mem,int nbVar, int nbNode) ;



#define NBCLAUSE 2
#define K 8

extern int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) ;
extern void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) ;


extern char *nom_des_actions[NBCLAUSE];

#endif
