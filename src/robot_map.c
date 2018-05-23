#include "robot_map.h"

#define STATES 4
#define BITS_PER_INT  (sizeof(int)*8)
enum cellState {
    stateUNKN = 0b00,
    stateFree = 0b01,
    stateBlock = 0b10,
    stateRover = 0b11
};

const char cellString[4] = {'U',' ','X','O'};
int states = STATES;
int states_bit = STATES/2;

int allocateMap(int* map, int rows, int columns) {

    int adjusted_size = calcAdjustedSize(rows, columns);

    map = (int*)calloc(adjusted_size, sizeof (int));

    return adjusted_size;
}

int getCell(int* map, int rows, int columns, int selected_row, int selected_column) {

    int adj_cell = selected_row*columns + selected_column;

    int mask = 0b11;

    int integer_cell = adj_cell*states_bit/(BITS_PER_INT);
    int shift = BITS_PER_INT - (BITS_PER_INT/states_bit - adj_cell - 1)*states_bit;

    int full_integer = map[integer_cell];

    int value = (full_integer >> shift) & mask;

    return value;
}

void setCell(int* map, int rows, int columns){

}

int calcAdjustedSize(int rows, int columns) {

    int adjusted_size = rows*columns*states_bit/(sizeof(int)*8) + 1;
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
