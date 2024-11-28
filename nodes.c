//
// Created by mongr on 14/11/2024.
//

#include "nodes.h"



t_node *createNode(int value, int nbSons) {

    t_node *newNode = (t_node*)malloc(sizeof(t_node));
    if (newNode == NULL) {
        // Gérer l'erreur d'allocation mémoire
        return NULL;
    }
    newNode->value = value;
    newNode->nbSons = nbSons;
    newNode->move=-1;
    newNode->orientation = -1;
    newNode->sons = (t_node**)malloc(nbSons * sizeof(t_node*));
    if (newNode->sons == NULL) {
        // Gérer l'erreur d'allocation mémoire
        free(newNode);
        return NULL;
    }
    for (int i = 0; i < nbSons; i++) {
        newNode->sons[i] = NULL;
    }

    return newNode;
}


int isleafnode(t_node *root)
{
    if(root->nbSons==0 || root->sons == NULL) return 1;

    for (int i = 0; i < root->nbSons; ++i) {
        if(root->sons[i]!=NULL)return 0;
    }
    return 1;
}