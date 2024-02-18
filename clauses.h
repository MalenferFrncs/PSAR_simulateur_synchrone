#ifndef CLAUSES_H
#define CLAUSES_H

#define NBCLAUSE 2

int (*gardes[NBCLAUSE])(int id) ;
void (*action[NBCLAUSE])(int id) ;

extern int action_id[NBSOMMET];

#endif
