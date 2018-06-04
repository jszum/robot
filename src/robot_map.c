#include "robot_map.h"

#define STATES 4
#define BITS_PER_INT  (sizeof(int)*8)

enum cS cellState;
enum rO roverOrientation;

const char cellString[] = {' ','O','X','#'};\
const char orntString[] = {'N','S','W','E'};
int states = STATES;
int states_bit = STATES/2;

int rover_row = 0;
int rover_column = 0;
int orientation = 0;

void placeRoverInMiddle(int* map, int rows, int columns) {
    int middle_row = rows/2;
    int middle_column = columns/2;

    rover_row = middle_row;
    rover_column = middle_column;

    orientation = oNorth;

    setCell(map, rows, columns, middle_row, middle_column, stateRover);
}


int* allocateMap(int rows, int columns) {

    int adjusted_size = calcAdjustedSize(rows, columns);
    int* map = (int*)calloc(adjusted_size, sizeof(int));

    placeRoverInMiddle(map, rows, columns);
    return map;
}

void turnLeft() {

    if(orientation == oNorth) orientation = oWest;
    else if(orientation == oWest)  orientation = oSouth;
    else if(orientation == oSouth) orientation = oEast;
    else if(orientation == oEast)  orientation = oNorth;

}

void turnRight(){
    if(orientation == oNorth) orientation = oEast;
    else if(orientation == oEast)  orientation = oSouth;
    else if(orientation == oSouth) orientation = oWest;
    else if(orientation == oWest)  orientation = oNorth;
}

void turnBack() {
    turnLeft();
    turnLeft();
}

int moveForward(int* map, int rows, int columns) {

    int rover_row_old = rover_row;
    int rover_column_old = rover_column;

    if(orientation == oNorth && rover_row > 0) {
        rover_row -= 1;
    }
    else if(orientation == oEast && rover_column < (columns-1))  {
        rover_column += 1;
    }
    else if(orientation == oSouth && rover_row < (rows-1)) {
        rover_row += 1;
    }
    else if(orientation == oWest && rover_column > 0) {
        rover_column -= 1;
    }
    else {
        return 1;
    }

    setCell(map, rows, columns, rover_row_old, rover_column_old, stateFree);
    setCell(map, rows, columns, rover_row, rover_column, stateRover);
    return 0;
}


void setNCellsAheadFree(int* map, int rows, int columns, int n) {

    int rover_row_var = rover_row;
    int rover_column_var = rover_column;


    int i = 0;
    for(i = 0; i<n; ++i) {
        if(orientation == oNorth) {
            rover_row_var -= 1;
        }
        else if(orientation == oEast)  {
            rover_column_var += 1;
        }
        else if(orientation == oSouth) {
            rover_row_var += 1;
        }
        else if(orientation == oWest) {
            rover_column_var -= 1;
        }

        if(isInRange(rows, columns, rover_row_var, rover_column_var)) {
            setCell(map, rows, columns, rover_row_var, rover_column_var, stateFree);
        }
        else {
            break;
        }
    }

}

void setNextCellFree(int* map, int rows, int columns) {
    setNCellsAheadFree(map, rows, columns, 1);
}

int isNextCellFree(int* map, int rows, int columns) {

    int rover_row_var = rover_row;
    int rover_column_var = rover_column;

    if(orientation == oNorth) {
        rover_row_var -= 1;
    }
    else if(orientation == oEast)  {
        rover_column_var += 1;
    }
    else if(orientation == oSouth) {
        rover_row_var += 1;
    }
    else if(orientation == oWest) {
        rover_column_var -= 1;
    }

    int status = getCell(map, rows, columns, rover_row_var, rover_column_var);

    return (status == stateFree);

}

int isInRange(int rows, int columns, int selected_row, int selected_column) {
    if(selected_row > 0 && selected_row < (rows-1)
            && selected_column > 0 && (selected_column < columns-1))
    {
        return 1;
    }
    else {
        return 0;
    }
}

void setCellAheadBlocked(int* map, int rows, int columns) {
    setCellBlockedAtDistance(map, rows, columns, 1);
}

void setCellBlockedAtDistance(int* map, int rows, int columns, int n) {

    int cell_ahead_row = rover_row;
    int cell_ahead_column = rover_column;

    if(orientation == oNorth) cell_ahead_row = rover_row-n;
    else if(orientation == oWest)  cell_ahead_column = rover_column -n;
    else if(orientation == oSouth) cell_ahead_row = rover_row+n;
    else if(orientation == oEast)  cell_ahead_column = rover_column+n;

    if(isInRange(rows, columns, cell_ahead_row, cell_ahead_column)) {
        setCell(map, rows, columns, cell_ahead_row, cell_ahead_column, stateBlock);
    }
}

int getCell(int* map, int rows, int columns, int selected_row, int selected_column) {

    int adj_cell = selected_row*columns + selected_column;

    int mask = 3;

    int integer_cell = adj_cell*states_bit/(BITS_PER_INT);
    int shift = BITS_PER_INT - (BITS_PER_INT/states_bit - adj_cell)*states_bit;

    int full_integer = map[integer_cell];

    int value = (full_integer >> shift) & mask;

    return value;
}

void setCell(int* map, int rows, int columns, int selected_row, int selected_column, int state){
    int adj_cell = selected_row*columns + selected_column;

    int integer_cell = adj_cell*states_bit/(BITS_PER_INT);
    int shift = BITS_PER_INT - (BITS_PER_INT/states_bit - adj_cell)*states_bit;

    int mask = 3;

    map[integer_cell] &= ~(mask << shift);
    map[integer_cell] |= (state << shift);
}

int calcAdjustedSize(int rows, int columns) {

    int adjusted_size = rows*columns*states_bit/(sizeof(int)*8) + 1;
    return adjusted_size;
}

int getBits(int integer, int shift) {

    return (integer >> shift) & 3;
}

#ifdef __linux__
void print_map(int* map, int rows, int columns)
{
    int size = calcAdjustedSize(rows, columns);
    int internal_size = (sizeof(int)*8/states_bit);
    int counter = 0;
    int i = 0;
    for(i = 0; i<size; ++i)
    {
        for(int j = 0; j<internal_size; ++j)
        {
            if((counter%columns)==0)
            {
                printf("\n");
            }
            if(counter == rows*columns) {
                break;
            }
            ++counter;
            int value = getBits(map[i], j*2);
            char sign = cellString[value];
            printf("[%c]", sign);
        }
    }
    printf("\n");
}
#endif
