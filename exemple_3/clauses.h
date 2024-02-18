#ifndef CLAUSES_H
#define CLAUSES_H

#define NBCLAUSE 2

extern int (*gardes[NBCLAUSE])(int id) ;
extern void (*action[NBCLAUSE])(int id) ;

extern int action_id[NBSOMMET];
extern char *nom_des_actions[NBCLAUSE];

#endif
