#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "trees.h"
#include "moves.h"
#include "path.h"
int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);




    t_move* moves = random_moves(9);
    for(int i = 0; i < 9; i++){
        t_move move = moves[i];
        printf("%s ", getMoveAsString(move));
        printf("%d ", remainingMoveNumber(move));
    }
    printf("\n");

    t_localisation spawn = SPAWN(6,7);
    printf("spawn point is y:%d x:%d\n",spawn.pos.y,spawn.pos.x);
    int border[2];
    border[0] = 6;
    border[1] = 7;


    int num_moves = 9;
    int usedmoveindices[num_moves];
    for(int i=0;i<num_moves;i++)
    {
        usedmoveindices[i]=0;
    }

    t_tree tree = createTree();
    /*tree.root = createNode(map.costs[spawn.pos.y][spawn.pos.x],num_moves);
    tree.root->orientation = spawn.ori;
    createPhase2(3,map,spawn,moves,num_moves,*(tree.root),usedmoveindices,border);*/

    tree.root = createphase4(map,spawn,0,5,moves,num_moves,usedmoveindices,border);
    printTree(tree.root,4);

    printf("done tree\n");
    t_move initialsequence[] = {};
    t_path result = findbestpath(tree.root,0,initialsequence,0);

    printf("Minimum value is: %d | Total cost is: %d | ",result.minval,result.totalcost);
    printf("Move sequence is: ");
    for (int i = 0; i < result.movecount-1; ++i) {
        printf("%s ", getMoveAsString(result.movesequence[i]));
    }

    return 0;
}








