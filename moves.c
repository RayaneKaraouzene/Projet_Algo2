//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
/* prototypes of local functions */
/* local functions are used only in this file, as helper functions */

/**
 * @brief Function to rotate the robot according to a move and its actual orientation
 * @param ori : the actual orientation of the robot
 * @param move : the move to do
 * @return the new orientation of the robot
 */
t_orientation rotate(t_orientation, t_move );



/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default:
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move,t_map map)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res = loc.pos;
    int rst;
    switch (map.soils[loc.pos.y][loc.pos.x]) {
        case ERG:
            switch (move)
            {
                case F_10:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y ;
                                break;
                        case EAST:
                            res.x = loc.pos.x ;
                                break;
                        case SOUTH:
                            res.y = loc.pos.y ;
                                break;
                        case WEST:
                            res.x = loc.pos.x ;
                                break;
                        default:
                            break;
                    }
                    break;
                case F_20:
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
                case F_30:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y - 2;
                                break;
                        case EAST:
                            res.x = loc.pos.x + 2;
                                break;
                        case SOUTH:
                            res.y = loc.pos.y +2;
                                break;
                        case WEST:
                            res.x = loc.pos.x - 2;
                                break;
                        default:
                            break;
                    }
                        break;
                case B_10:
                    switch (loc.ori) {
                        case NORTH:
                            res.y = loc.pos.y ;
                                break;
                        case EAST:
                            res.x = loc.pos.x ;
                                break;
                        case SOUTH:
                            res.y = loc.pos.y ;
                                break;
                        case WEST:
                            res.x = loc.pos.x ;
                                break;
                        default:
                            break;
                    }
                        break;
                case T_LEFT:
                    loc.ori=loc.ori;
                        break;
                case T_RIGHT:
                    loc.ori=loc.ori;
                        break;
                case U_TURN:
                    loc.ori=(loc.ori+1)%4;
                        break;
                default:
                    break;
            }
            break;

        default:
            switch (move)
            {
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
        break;
    }
        return loc_init(res.x, res.y, loc.ori);

}


/* definitions of exported functions */

char *getMoveAsString(int move)
{
    if(move==-1) return "START";
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move,t_map map)
{
    t_localisation new_loc;
    new_loc.ori = rotate(loc.ori, move);
    new_loc = translate(loc, move, map);
    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m,t_map map)
{
    *p_loc = move(*p_loc, m, map);
    return;
}



int remainingMoveNumber(t_move move){
    return moves_count[move];
}

void decrementMoveNumber(t_move move){
    moves_count[move] -= 1;
}

t_move intToMove(int index){
    switch(index){
        case 0:
            return F_10;
        case 1:
            return F_20;
        case 2:
            return F_30;
        case 3:
            return B_10;
        case 4:
            return T_LEFT;
        case 5:
            return T_RIGHT;
        case 6:
            return U_TURN;
        default:
            return 0;
    }
}

t_move* random_moves(int n){
    t_move* moves = (t_move*) malloc(sizeof(t_move) * n);
    srand(time(NULL));
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