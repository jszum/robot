#include <stdio.h>
#include <stdlib.h>

#include "robot_map.h"

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    int* map = NULL;
    int rows = 11;
    int columns = 11;


    int mapsize = calcAdjustedSize(rows, columns);
    //map = (int*)calloc(mapsize, sizeof(int));
    map = allocateMap(rows, columns);

    printf("C-required size = %d\n", rows*columns);
    printf("Opt required size = %d\n", mapsize);

    int sign = getCell(map,rows,columns,4,2);
    moveForward(map, rows, columns);
    moveForward(map, rows, columns);
    moveForward(map, rows, columns);
    setNextCellFree(map, rows, columns);
    turnLeft();
    moveForward(map, rows, columns);
    moveForward(map, rows, columns);
    setCellBlockedAtDistance(map, rows, columns, 2);
    turnRight();
    setCellAheadBlocked(map, rows, columns);
    turnBack();
    setNCellsAheadFree(map,rows,columns,5);
    int status = isNextCellFree(map, rows, columns);


    print_map(map,rows,columns);
    return 0;
}

//nxn = n^2 ints
//1 int = 8 bits
//nxn = n^2 * 2 bits = 2n^2 bits
//2n^2/sizeof(int) =
