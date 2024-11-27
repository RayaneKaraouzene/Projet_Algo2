#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "trees.h"
#include "moves.h"
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
    t_tree tree = createTree();
    int mapval = map.costs[spawn.pos.y][spawn.pos.x];
    tree.root = createNode(mapval,4);
    createPhase(3,map,spawn,moves,4,*(tree.root),0,border);
    printTree(tree.root,4);


    return 0;
}








