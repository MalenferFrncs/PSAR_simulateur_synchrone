#ifndef MACRO_H
#define MACRO_H

#include "topologie.h"

#define NBMACRO 1

extern int macro_mem[NBSOMMET][NBMACRO] ;

extern int (*macro[NBMACRO])(int id) ;


#endif
