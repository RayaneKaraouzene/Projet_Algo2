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


/**
* @brief Prints the tree
*/
void printTree(t_node *root, int depth);

/**
* @brief Function to create the phase known as the tree of all possibilities of moves
* @param map : the map
* @param loc : the location of the rover, the spawn point at the start
* @param depth : the starting depth, initiated at 0
 * @param maxdepth : the max depth, also said to be the number of moves that are going to be chosen
 * @param movelist : the list of the moves
 * @param movescount : the size of movelist
 * @param usedmoves : an array used to determine which move has been used
 * @param border : an array containing map borders x,y
* @return the root
*/
t_node* createphase4(t_map map,t_localisation loc,int depth,int maxdepth,t_move *movelist,int movescount,int *usedmoves,int *border);

#endif //UNTITLED1_TREES_H

