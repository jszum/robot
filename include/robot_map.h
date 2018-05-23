#ifndef ROBOT_MAP_H
#define ROBOT_MAP_H

#include <stdlib.h>

int allocateMap(int* map, int rows, int columns);
int getCell(int* map, int rows, int columns, int row, int column);
void setCell(int* map, int rows, int columns);
int calcAdjustedSize(int rows, int columns);

#ifdef __linux__
void print_map(int* map, int rows, int columns);
#endif


#endif // ROBOT_MAP_H
