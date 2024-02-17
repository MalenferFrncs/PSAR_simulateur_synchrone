#ifndef CLAUSES_H
#define CLAUSES_H

#define NBCLAUSE 2

int (*gardes[NBCLAUSE])(int id) ;
void (*action[NBCLAUSE])(int id) ;

int action_id[NBSOMMET] = {0,0,0,0,0,0,0,0};

#endif