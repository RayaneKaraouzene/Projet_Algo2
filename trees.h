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
t_node* createphase1(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,int border[],int *usedmoveindices);
void createPhase2(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,t_node root,int *usedmove,int border[]);
t_node* createphase3(t_map map,t_localisation loc,int depth,int maxdepth,t_move *movelist,int movescount,int *usedmoves,int *border);
t_node* createphase4(t_map map,t_localisation loc,int depth,int maxdepth,t_move *movelist,int movescount,int *usedmoves,int *border);

#endif //UNTITLED1_TREES_H

