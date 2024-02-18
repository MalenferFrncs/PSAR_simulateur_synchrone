#ifndef MACRO_H
#define MACRO_H

#include "topologie.h"

#define NBMACRO 1
int new_clock_value(int id);

extern int macro_mem[NBSOMMET][NBMACRO] ;

extern int (*macro[NBMACRO])(int id) ;


#endif
