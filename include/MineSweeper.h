/* system header files */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* struct members for the Cell */
typedef struct Cell{
    int number_of_mines;
    char ch;
    bool uncovered;
    bool bomb;
}Cell;

/* struct members for height and width of board and 2 dimensional array of cells */
typedef struct Board{
    int height, width;
    Cell **cells; /* pointer to the pointer */
}Board;

void make_board(Board*); /* pointer to the board in order to create board */
void print_board(Board*); /* pointer to the board and printing board */
void bombplacing_randomly(Board*, int); /* pointer to the board and number of bombs  */
void numof_adjacent_mines(Board*); /* pointer to the board and determining number of bombs in adjacency cells */
void uncover(Board*, int, int); /* pointer to the board and selected coordinates by the user for uncovering cells */
void reveal_automatically(Board*, int, int); /* pointer to the board and cell's coordinates for automatic reveal of cells */
void check_for_win(Board*, int); /* pointer to the board and number of mines  */
void play_game(); /* function to play the game */
