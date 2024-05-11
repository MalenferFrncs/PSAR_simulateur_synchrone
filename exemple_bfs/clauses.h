#ifndef CLAUSES_H
#define CLAUSES_H

#define NBMACRO 3

#define FALSE 0
#define TRUE 1
#define WAIT 2
#define ER 3
#define ZERO_ROOT -1



extern int (*macro[NBMACRO])(int id,int **topologie, int **var,int **macro_mem, int nbNode, int nbVar) ;

#define NBCLAUSE 8

extern int (*gardes[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id) ;
extern void (*action[NBCLAUSE])(int id,int **topologie, int **var, int nbNode, int nbVar,int **macro_mem,int *action_id, int **var_prec) ;


extern char *nom_des_actions[NBCLAUSE];



#endif
