#ifndef TOPOLOGIE_H
#define TOPOLOGIE_H

#define NBSOMMET 8
#define NBVAR 1


int topologie[NBSOMMET][NBSOMMET]= {
    {0,1,0,0,0,0,0,0},
    {1,0,1,0,1,0,0,0},
    {0,1,0,1,0,1,1,0},
    {0,0,1,0,0,0,1,0},
    {0,1,0,0,0,1,0,1},
    {0,0,1,0,1,0,0,1},
    {0,0,1,1,0,0,0,1},
    {0,0,0,0,1,1,1,0}
};

int var[NBSOMMET][NBVAR] = {
    {7},
    {8},
    {4},
    {3},
    {2},
    {7},
    {0},
    {7}
}



#endif