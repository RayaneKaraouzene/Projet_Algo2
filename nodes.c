//
// Created by mongr on 14/11/2024.
//

#include "nodes.h"



t_node *createNode(int value, int nbSons, int depth) {
    t_node *newNode = (t_node*)malloc(sizeof(t_node));

    newNode->value = value;
    newNode->depth = depth;
    newNode->nbSons = nbSons;

    newNode->sons = (t_node**)malloc(nbSons * sizeof(t_node*));

    for (int i = 0; i < nbSons; i++) {
        newNode->sons[i] = NULL;
    }

    return newNode;
}
