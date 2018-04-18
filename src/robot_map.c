#include "robot_map.h"


enum cellState {
    state0 = 0b00,
    state1 = 0b01,
    state2 = 0b10,
    state3 = 0b11
};

int allocateMap(int* map, int rows, int columns) {

    int adjusted_size = calcAdjustedSize(rows, columns);

    map = calloc(adjusted_size, sizeof (int));

    return adjusted_size;
}

int getCell(int* map, int rows, int columns) {

    int adjusted_size = calcAdjustedSize(rows, columns);


}

void setCell(int* map, int rows, int columns){

}

int calcAdjustedSize(int rows, int columns) {

    int states = 4;
    int states_bit = states/2;

    int adjusted_size = rows*columns*states_bit/(sizeof(int)*8);
    return adjusted_size;
}

#ifdef __linux__
void print_map(int* map, int rows, int columns)
{
    int i = 0;
    for(i = 0; i<rows*columns; ++i)
    {
        if((i%columns)==0)
        {
            printf("\n");
        }

        printf("[%s]", " ");
    }
    printf("\n");
}
#endif
