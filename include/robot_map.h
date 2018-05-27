#ifndef ROBOT_MAP_H
#define ROBOT_MAP_H

#include <stdlib.h>
#include <stdio.h>

enum cellState {
    stateUNKN = 0b00,
    stateFree = 0b01,
    stateBlock = 0b10,
    stateRover = 0b11
};


enum roverOrientation {
    oNorth = 0,
    oSouth = 1,
    oWest  = 2,
    oEast  = 3
};

int* allocateMap(int rows, int columns);
int getCell(int* map, int rows, int columns, int row, int column);
void setCell(int* map, int rows, int columns, int selected_row, int selected_column, int state);
int calcAdjustedSize(int rows, int columns);
int getBits(int integer, int shift);
int moveForward(int* map, int rows, int columns);
void turnLeft();
void turnRight();
void turnBack();

int isNextCellFree(int* map, int rows, int columns);
void setNextCellFree(int* map, int rows, int columns);

void setCellAheadBlocked(int* map, int rows, int columns);
void setCellBlockedAtDistance(int* map, int rows, int columns, int n);
void setNCellsAheadFree(int* map, int rows, int columns, int n);
int isInRange(int rows, int columns, int selected_row, int selected_column);

#ifdef __linux__
void print_map(int* map, int rows, int columns);
#endif


#endif // ROBOT_MAP_H
