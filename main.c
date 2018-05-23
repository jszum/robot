#include <stdio.h>
#include <stdlib.h>

#include "robot_map.h"

int main(int argc, char *argv[])
{
    int* map = NULL;
    int rows = 5;
    int columns = 3;


    int mapsize = calcAdjustedSize(rows, columns);
    map = (int*)calloc(mapsize, sizeof(int));

    printf("C-required size = %d\n", rows*columns);
    printf("Opt required size = %d\n", mapsize);


    int value = getCell(map,rows,columns,2,1);

    print_map(map,rows,columns);
    return 0;
}

//nxn = n^2 ints
//1 int = 8 bits
//nxn = n^2 * 2 bits = 2n^2 bits
//2n^2/sizeof(int) =
