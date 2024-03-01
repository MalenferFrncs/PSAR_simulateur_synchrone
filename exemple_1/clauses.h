#ifndef CLAUSES_H
#define CLAUSES_H

#define NBCLAUSE 2

extern int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) ;
extern void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) ;


extern char *nom_des_actions[NBCLAUSE];

#endif
