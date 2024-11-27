//
// Created by Rayane Karaouzene on 14/11/2024.
//



#ifndef UNTITLED1_TREES_H
#define UNTITLED1_TREES_H

#include "stdlib.h"
#include <stdio.h>
#include "nodes.h"
#include "map.h"

typedef struct tree
{
    t_node *root;
}t_tree;

t_tree createTree();
void createPhase(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,t_node root,int usedmove,int border[]);
void printTree(t_node *root, int depth);


#endif //UNTITLED1_TREES_H

