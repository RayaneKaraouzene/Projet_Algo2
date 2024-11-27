#include <stdio.h>
#include "map.h"
#include "loc.h"
#include "trees.h"
#include "moves.h"
#include "path.h"
int main() {
    t_map map;
    t_map mapcopy;

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
    mapcopy = copyMap(map);




    t_localisation spawn = SPAWN(6,7);

    printf("spawn point is y:%d x:%d orientation : %s \n",spawn.pos.y,spawn.pos.x,getOriAsString(spawn.ori));
    int border[2];
    border[0] = 6;
    border[1] = 7;
    map.soils[spawn.pos.y][spawn.pos.x] = ROVER;
    displayMap(map);


    int num_moves = 5;

    int running = 1;
    spawn.pos.y = 1;
    spawn.pos.x = 1;
    spawn.ori = 'EAST';

    do
    {

        srand(time(NULL));
        t_move* moves = random_moves(num_moves);
        for(int i = 0; i < num_moves; i++){
            t_move move = moves[i];
            printf("%s ", getMoveAsString(move));
            printf("%d ", remainingMoveNumber(move));
        }
        printf("\n");

        int usedmoveindices[num_moves];
        for(int i=0;i<num_moves;i++)
        {
            usedmoveindices[i]=0;
        }


        t_tree tree = createTree();
        /*tree.root = createNode(map.costs[spawn.pos.y][spawn.pos.x],num_moves);
        tree.root->orientation = spawn.ori;
        createPhase2(3,map,spawn,moves,num_moves,*(tree.root),usedmoveindices,border);*/

        tree.root = createphase4(map,spawn,0,3,moves,num_moves,usedmoveindices,border);


        printf("done tree\n");
        t_move initialsequence[] = {};
        t_path result = findbestpath(tree.root,0,initialsequence,0);

        printf("Minimum value is: %d | Total cost is: %d | ",result.minval,result.totalcost);
        printf("Move sequence is: ");
        for (int i = 0; i < result.movecount-1; ++i) {
            printf("%s ", getMoveAsString(result.movesequence[i]));
        }


        int old_x =spawn.pos.x;
        int old_y =spawn.pos.y;
        int old_ori =spawn.ori;

        printf("\n");
        for (int i = 0; i < result.movecount-1; ++i) {
            t_localisation t =  translate(loc_init(old_x,old_y,old_ori),result.movesequence[i],map);
            if (old_ori == t.ori)
            {
                map.soils[t.pos.y][t.pos.x] = ROVER;
                map.soils[old_y][old_x] = mapcopy.soils[old_y][old_x];
                old_x = t.pos.x;
                old_y = t.pos.y;
                old_ori = t.ori;
                printf("\n %d \n",i)  ;
            }
            printf("\n\n\n");
            displayMap(map);

        }
        if (result.minval == 0 || result.minval >= 10000)
        {
            running = 0;
            printf("fini");
        }

        spawn.pos.x = old_x;
        spawn.pos.y = old_y;
        spawn.ori = old_ori;
        printf("%d %d %s\n",spawn.pos.x,spawn.pos.y,getOriAsString(spawn.ori));
        freetree(tree.root);
        free(&tree);

    }while(running !=0 );

    printf("hdjohbzmocgbzimpcbz");






    return 0;
}





