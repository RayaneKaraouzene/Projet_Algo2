//
// Created by Rayane Karaouzene on 14/11/2024.
//


#include "trees.h"
#include "map.h"
#include "moves.h"

#define NUM_MOVES 3
t_tree createTree()
{

    t_tree tree;
    tree.root = NULL;
    return tree;

}




/*t_tree createPhasee(t_localisation spawncoords,t_map map,t_move movelist[],int movelist_size)
{
    int spawn_x = spawncoords.x;
    int spawn_y = spawncoords.y;


    t_localisation current_loc;
    current_loc.pos.x = spawn_x;
    current_loc.pos.y = spawn_y;
    current_loc.ori = spawncoords.ori;


    t_tree phase = createTree();

    int spawnval = map.costs[spawn_y][spawn_x];

    phase.root = createNode(spawnval,movelist_size,phase.root);

    t_node *currentnode = phase.root;
    t_node *mothernode = phase.root;
    for (int i = 0; i < movelist_size; ++i) {
        mothernode = mothernode->sons[i];
        for (int j = 0; j < movelist_size; ++j) {


            for(int k=0;k<movelist_size;k++)
            {
                currentnode = mothernode->sons[k];

                current_loc = translate(current_loc,movelist[k]);
                int mapval = map.costs[current_loc.pos.y][current_loc.pos.x];
                currentnode = createNode(mapval,movelist_size,mothernode);
                currentnode->move = movelist[k];

            }
            mothernode = currentnode->parent->sons[j];
        }
        movelist_size--;

    }



}*/

void createPhase(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,t_node root,int usedmove,int border[])
{
    if (tries == 0) return;

    for (int i = 0; i < NUM_MOVES; ++i) {
        if((usedmove >>i)&1) continue;
        if (root.value>10000) return;
        if (root.value==0)return;
        t_localisation newloc;
        newloc.pos.x = loc.pos.x;
        newloc.pos.y = loc.pos.y;
        newloc.ori = loc.ori;


        newloc = translate(newloc,movelist[i],map);
        int mapval;
        if(newloc.pos.x>=0 && newloc.pos.x<border[0] && newloc.pos.y>=0
        && newloc.pos.y<border[1])
        {
             mapval = map.costs[newloc.pos.y][newloc.pos.x];
        }
        else
        {
             mapval = 20000;
        }
        t_node *newnode = createNode(mapval,movelist_size);
        newnode->move = movelist[i];
        newnode->orientation = newloc.ori;
        root.sons[i] = newnode;

        if(root.value<10000)
        {
            createPhase(tries-1,map,newloc,movelist,movelist_size-1,*newnode,usedmove | (1 << i),border);
        }



    }
}

void printTree1(t_node *root, int depth) {
    if (!root) {
        return; // Base case: if the node is NULL, return
    }

    // Print the indentation based on the depth of the node
    for (int i = 0; i < depth; i++) {
        printf("    "); // Indentation for each level
    }


    // Print the value of the current node
    printf("└── Node Value: %d |Move used: %d\n", root->value,root->move);

    // Recur for each child node
    for (int i = 0; i < root->nbSons; i++) {
        if (root->sons[i]) { // Only print non-NULL children
            printTree(root->sons[i], depth + 1); // Recur with increased depth
        }
    }
}

void printTree(t_node *root, int depth) {
    if (!root) {
        return; // Si le nœud est NULL, on sort
    }

    // Affichage du préfixe (indentation et branche selon la profondeur)
    for (int i = 0; i < depth - 1; i++) {
        printf("|   "); // Branche verticale pour les niveaux supérieurs
    }
    if (depth > 0) {
        printf("+--- "); // Branche finale pour le nœud actuel
    }

    // Afficher le contenu du nœud
    printf("Node Value: %d | Move used: %s | orientation: %s\n", root->value, getMoveAsString(root->move),
           getOriAsString(root->orientation));

    // Appel récursif pour chaque fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i], depth + 1);
    }
}

