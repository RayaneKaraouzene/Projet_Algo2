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
t_localisation translate(t_localisation loc, t_move move);
void createPhase(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,t_node root,int usedmove,int border[]);
void printTree(t_node *root, int depth);
t_node* createphase1(int tries