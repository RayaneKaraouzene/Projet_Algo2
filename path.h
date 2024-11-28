//
// Created by Rayane Karaouzene on 27/11/2024.
//

#ifndef UNTITLED1_PATH_H
#define UNTITLED1_PATH_H
#include "limits.h"
#include "nodes.h"
#include "trees.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct
{
    int minval;
    int totalcost;
    t_move* movesequence;
    int movecount;
    t_node *bestnode;
}t_path;

t_path findbestpath(t_node *root,int currentcost,t_move* currentsequence,int movecount);
#endif //UNTITLED1_PATH_H




