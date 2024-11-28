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


/**
* @brief Function to create the phase known as the tree of all possibilities of moves
* @param root :
* @param currentcost : the current cost to reach a leaf
* @param currentsequence : the sequence done to reach a leaf, initiated at none
 * @param movecount : the number of moves picked
* @return the root
*/
t_path findbestpath(t_node *root,int currentcost,t_move* currentsequence,int movecount);
#endif //UNTITLED1_PATH_H




