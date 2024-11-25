//
// Created by mongr on 14/11/2024.
//
#include "stdlib.h"
#include <stdio.h>
#include "moves.h"
#ifndef UNTITLED1_NODES_H
#define UNTITLED1_NODES_H


typedef struct s_node {
    int value;
    t_move move;
    int depth;
    struct s_node **sons; // Tableau de pointeurs pour les enfants
    int nbSons; // Taille physique du tableau des enfants
    t_orientation orientation;
} t_node;

/**
 * @brief create a new node
 * @param value of the node; nbSons physical size of the child array ; deth node depth
 * @return newNode
 */
t_node *createNode(int value, int nbSons);



#endif //UNTITLED1_NODES_H
