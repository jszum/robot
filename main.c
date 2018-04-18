#include <stdio.h>
#include <stdlib.h>

#include "robot_map.h"

int main(int argc, char *argv[])
{
    int* map = NULL;
    int mapsize = allocateMap(map, 10, 10);

    printf("Required size = %d\n", mapsize);


    print_map(map,10,10);
    return 0;
}

//nxn = n^2 ints
//1 int = 8 bits
//nxn = n^2 * 2 bits = 2n^2 bits
//2n^2/sizeof(int) =
