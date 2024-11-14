#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "moves.h"

t_move* random_moves(int n){
    t_move* moves = (t_move*) malloc(sizeof(t_move) * n);
    for(int i = 0; i < n; i++){
        int min = 0;
        int max = 6;
        int rand_index = rand() % (max - min + 1) + min;
        t_move next_move = intToMove(rand_index);
        decrementMoveNumber(next_move);
        *(moves+i) = next_move;
    }
    return moves;
}

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

    for(int j = 0; j < 7; j++){
        printf("%s ", getMoveAsString(intToMove(j)));
        printf("%d ", remainingMoveNumber(intToMove(j)));
    }
    printf("\n");

    t_move* moves = random_moves(9);
    for(int i = 0; i < 9; i++){
        t_move move = moves[i];
        printf("%s ", getMoveAsString(move));
        printf("%d ", remainingMoveNumber(move));
    }
    return 0;
}

//test





