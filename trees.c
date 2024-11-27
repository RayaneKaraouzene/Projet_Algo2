//
// Created by Rayane Karaouzene on 14/11/2024.
//


#include "trees.h"
#include "map.h"
#include "moves.h"

#define NUM_MOVES 4
t_tree createTree()
{

    t_tree tree;
    tree.root = NULL;
    return tree;

}


t_localisation translatee(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    int rst;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        case T_LEFT:
            loc.ori=(loc.ori+3)%4;
            break;
        case T_RIGHT:
            loc.ori=(loc.ori+1)%4;
            break;
        case U_TURN:
            loc.ori=(loc.ori+2)%4;
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori);

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

        newloc = translate(newloc,movelist[i]);
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


t_node* createphase1(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,int border[],int *usedmoveindices)
{
    if(tries == 0) return NULL;


    int nbsons = 0;
    for (int i = 0; i < movelist_size; ++i) {


        if(!usedmoveindices[i])
        {
            t_localisation newloc;
            newloc.pos.x = loc.pos.x;
            newloc.pos.y = loc.pos.y;
            newloc.ori = loc.ori;
            newloc = translate(newloc,movelist[i]);
            if(newloc.pos.x>=0 && newloc.pos.x<border[0] && newloc.pos.y>=0
               && newloc.pos.y<border[1])
            {
                nbsons++;
            }
        }

    }

    t_node *newnode = createNode(map.costs[loc.pos.y][loc.pos.x],nbsons);

    int childindex = 0;
    for (int i = 0; i < movelist_size; ++i) {
        if(usedmoveindices[i]) continue;
        t_move move = movelist[i];

        t_localisation newloc;
        newloc.pos.x = loc.pos.x;
        newloc.pos.y = loc.pos.y;
        newloc.ori = loc.ori;
        newloc = translate(newloc,movelist[i]);
        if(newloc.pos.x<0 || newloc.pos.x>=border[0] || newloc.pos.y<0
           && newloc.pos.y>=border[1])
            continue;

        int newUsedmoveindices[movelist_size];
        for (int j = 0; j < movelist_size; ++j) {
            newUsedmoveindices[j] = usedmoveindices[j];
        }
        newUsedmoveindices[i]=1;

        newnode->orientation = loc.ori;
        newnode->move = move;
        newnode->sons[childindex++] = createphase1(tries-1,map,newloc,movelist,movelist_size,border,newUsedmoveindices);
    }
    return newnode;
}

void createPhase2(int tries,t_map map,t_localisation loc,t_move movelist[],int movelist_size,t_node root,int *usedmove,int border[])
{
    if (tries == 0) return;

    int nbsons = 0;
    for (int i = 0; i < movelist_size; ++i) {
        if(!usedmove[i])
        {
            t_localisation newloc;
            newloc.pos.x = loc.pos.x;
            newloc.pos.y = loc.pos.y;
            newloc.ori = loc.ori;
            newloc = translate(newloc,movelist[i]);


            if(newloc.pos.x>=0 && newloc.pos.x<border[0] && newloc.pos.y>=0
               && newloc.pos.y<border[1])
            {
                nbsons++;
                if (map.costs[newloc.pos.y][newloc.pos.x]>=10000 || map.costs[newloc.pos.y][newloc.pos.x]==0) nbsons = 0;
            }

        }
    }



    for (int i = 0; i < movelist_size; ++i) {
        if(!usedmove[i]) {
            t_localisation newloc;
            newloc.pos.x = loc.pos.x;
            newloc.pos.y = loc.pos.y;
            newloc.ori = loc.ori;

            newloc = translate(newloc, movelist[i]);
            int mapval;


            if (newloc.pos.x >= 0 && newloc.pos.x < border[0] && newloc.pos.y >= 0
                && newloc.pos.y < border[1]) {

                mapval = map.costs[newloc.pos.y][newloc.pos.x];

            } else {
                mapval = 20000;
            }
            
            int newusedmove[movelist_size];
            for (int j = 0; j < movelist_size; ++j) {
                newusedmove[j] = usedmove[j];
            }
            newusedmove[i]=1;

            t_node *newnode = createNode(mapval,nbsons);
            newnode->move = movelist[i];
            newnode->orientation = newloc.ori;
            root.sons[i] = newnode;
            createPhase2(tries - 1, map, newloc, movelist, movelist_size, *newnode,newusedmove, border);

        }
    }
}


t_node* createphase3(t_map map,t_localisation loc,int depth,int maxdepth,t_move *movelist,int movescount,int *usedmoves,int *border)
{
    if(depth==maxdepth) return NULL;


    int nbsons = movescount-depth;
    t_node *newnode = createNode(map.costs[loc.pos.y][loc.pos.x],nbsons);


    int childindex = 0;

    for (int i = 0; i < movescount; ++i) {
        if(usedmoves[i]) continue;
        t_localisation newloc;
        newloc.pos.x = loc.pos.x;
        newloc.pos.y = loc.pos.y;
        newloc.ori = loc.ori;
        newloc = translate(newloc,movelist[i]);

        int childvalue;

        if (newloc.pos.x < 0 || newloc.pos.x >= border[0] || newloc.pos.y < 0
            || newloc.pos.y >= border[1]) childvalue = 20000;
        else childvalue = map.costs[newloc.pos.y][newloc.pos.x];

        int newusedmoves[movescount];
        for (int j = 0; j < movescount; ++j) {
            newusedmoves[j]=usedmoves[j];
        }
        usedmoves[i]=1;
        if (childvalue>=10000)
        {
            newnode->sons[childindex++] = createNode(childvalue,0);
            if(newnode->sons[childindex-1])
            {
                newnode->sons[childindex-1]->move = movelist[i];
                newnode->sons[childindex-1]->orientation = newloc.ori;
            }
        }
        else
        {
            newnode->sons[childindex++] = createphase3(map,newloc,depth+1,maxdepth,movelist,movescount,newusedmoves,border);
            if(newnode->sons[childindex-1])
            {
                newnode->sons[childindex-1]->move = movelist[i];
                newnode->sons[childindex-1]->orientation = newloc.ori;
            }
        }
    }
    return newnode;
}


t_node* createphase4(t_map map,t_localisation loc,int depth,int maxdepth,t_move *movelist,int movescount,int *usedmoves,int *border)
{
    if(depth==maxdepth) return NULL;


    t_node *root = createNode(map.costs[loc.pos.y][loc.pos.x],movescount-depth);

    if(root->value>=10000)
    {
        root->nbSons = 0;
        return root;
    }

    int nbsons = 0;

    for (int i = 0; i < movescount; ++i) {
        if(usedmoves[i])
        {
            continue;
        }
        t_localisation newloc;
        newloc.pos.x = loc.pos.x;
        newloc.pos.y = loc.pos.y;
        newloc.ori = loc.ori;
        newloc = translate(newloc,movelist[i]);

        int childvalue;
        if (newloc.pos.x < 0 || newloc.pos.x >= border[0] || newloc.pos.y < 0
            || newloc.pos.y >= border[1])
        {
            childvalue = 20000;
        }
        else childvalue = map.costs[newloc.pos.y][newloc.pos.x];


        int newusedmoves[movescount];
        for (int j = 0; j < movescount; ++j) {
            newusedmoves[j]=usedmoves[j];
        }
        newusedmoves[i]=1;

        t_node *child = createNode(childvalue,movescount-depth-1);
        child->move = movelist[i];
        child->orientation = newloc.ori;

        if(child->value>=10000)child->nbSons = 0;
        else{
            child->sons = (t_node**)malloc((movescount-depth-1) * sizeof(t_node*));
            t_node* subtree = createphase4(map,newloc,depth+1,maxdepth,movelist,movescount,newusedmoves,border);
            if(subtree)
            {
                for (int j = 0; j < subtree->nbSons; ++j) {
                    child->sons[j]= subtree->sons[j];
                }
                child->nbSons=subtree->nbSons;
            }
        }

        root->sons[nbsons++]=child;

    }
    root->nbSons = nbsons;
    return root;
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
            printTree1(root->sons[i], depth + 1); // Recur with increased depth
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
    printf("Node Value: %d | Move used: %s | orientation: %s | nbsons:%d\n", root->value, getMoveAsString(root->move),
           getOriAsString(root->orientation),root->nbSons);

    // Appel récursif pour chaque fils
    for (int i = 0; i < root->nbSons; i++) {
        printTree(root->sons[i], depth + 1);
    }
}



