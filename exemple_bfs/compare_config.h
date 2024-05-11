#ifndef COMPARE_CONFIG_H
#define COMPARE_CONFIG_H

struct _past_config{
    int ** config;
    struct _past_config *next;
};

typedef struct _past_config config_mem;

int **copy_config(int **src, int nbNode, int nbVar);

config_mem *past_init(int **current_config,int nbNode,int nbVar);

int check_past(int ** curent_config, config_mem **past, int nbNode,int nbVar,FILE* sortie);

#endif