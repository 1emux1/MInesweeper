/* user header file */
#include "MineSweeper.h"

/* Global variables before starting game,assigning false to them*/
bool lose = false;
bool win = false;

void make_board(Board *ptr)
{
    int i, j;
    ptr->cells=(Cell**)malloc((ptr->height+2)*sizeof(Cell*)); /* array of pointers*/

    for(i = 0; i <= ptr->height+1; ++i)
        ptr->cells[i]=(Cell*)malloc((ptr->width+2)*sizeof(Cell)); /* dynamic 2 dimensional array of cells and creating cells in board*/
    for(i = 0; i <= ptr->height+1; ++i){
        for(j = 0; j <= ptr->width+1; ++j){
            if (i==0 || i==ptr->height+1 || j==0 || j==ptr->width+1)
            {
                ptr->cells[i][j].bomb = false;
                ptr->cells[i][j].uncovered = true;
            }

            else
            {
                ptr->cells[i][j].ch = '-';  // making cells with character '-'
                ptr->cells[i][j].number_of_mines = 0; // before the game it is zero
                ptr->cells[i][j].bomb = false; // there is no bomb before the game
                ptr->cells[i][j].uncovered = false;
            }
        }
    }

     return;
}

void print_board(Board *ptr)
{
    system("cls"); // clearing the screen

    printf("  ");
    int i, j;
    for(i = 1; i <= ptr->width; ++i) /* loop in order print each row */
        printf("%d ", i); // numbers which shows rows
    printf("\n");
    /* nested loop in order to print numbers for columns and characters for cells */
    for(i = 1; i <= ptr->height; ++i){
        for(j = 0; j<= ptr->width; ++j){
          if(j == 0) printf("%d ", i);   // number which shows columns
          else printf("%c ", ptr->cells[i][j].ch); // printing cells in the board
        }
        printf("\n");
    }
   return;
}

void bombplacing_randomly(Board *ptr, int mines)
{
    int random_row, random_col, num_of_mine = 0;
    while(num_of_mine < mines)
    {
        random_row = rand()%ptr->height+1; // generating random number
        random_col = rand()%ptr->width+1;  // generating random number

        if(ptr->cells[random_row][random_col].bomb == false && (random_row != 0 && random_col != 0)) // checking for numbers which were generated before or not
        {
            ptr->cells[random_row][random_col].bomb = true; // if not, make a new bomb
            num_of_mine++;
        }
    }
     return;
}

void numof_adjacent_mines(Board *ptr)
{
    /*
	Count all the mines in the 8 adjacent
        cells

      (i-1,j-1)  (i-1,j) (i-1,j+1)
              \    |    /
               \   |   /
        (i,j-1)---CELL---(i,j+1)
                 / |  \
               /   |    \
       (i+1,j-1) (i+1,j) (i+1,j+1)
    */

	int i, j, m, n;
	for(i = 1; i <= ptr->height; ++i){
        for(j = 1; j <= ptr->width; ++j){
            if (ptr->cells[i][j].bomb==false){
                for(m = i-1; m <= i+1; ++m)
                for(n = j-1; n <= j+1; ++n)
                    if(ptr->cells[m][n].bomb == true) // checking number of bombs in adjacent cell
                    ptr->cells[i][j].number_of_mines++;
            }
        }
    }
    return;
}

void uncover(Board *ptr, int a, int b)
{
    if(ptr->cells[a][b].bomb == true)
    {
        lose = true; // terminate the game "in the play game function (while loop)"
        int i, j;
        /* nested loop to uncover cells */
        for(i = 1; i <= ptr->height; ++i)
            for(j = 1; j <= ptr->width; ++j)
               if(ptr->cells[i][j].bomb == true) /* if there is a bomb */
                  ptr->cells[i][j].ch = '*'; // showing all bombs
               else
                  ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; // putting number of mines in surrounding cells
        print_board(ptr);
        printf("\nYou Lost\n");
        printf("Game Over\n");

         return;
    }

   ptr->cells[a][b].ch = ptr->cells[a][b].number_of_mines + '0'; //  showing number of bombs in the cell
    if(ptr->cells[a][b].number_of_mines == 0)
       reveal_automatically(ptr,a,b); // if number of bomb is 0 in cell then reveal automatically
    else
       ptr->cells[a][b].uncovered = true;

    return;
}

void reveal_automatically(Board *ptr, int a, int b)
{
    int i, j;

    if(ptr->cells[a][b].uncovered == false)
    {
        ptr->cells[a][b].uncovered = true;
        /* nested loop to reveal automatically */
        for(i = a-1; i <= a+1; ++i)
            for(j = b-1; j <= b+1; ++j)
               if(ptr->cells[i][j].uncovered == false)
                 uncover(ptr,i,j); //calling function in order to uncover cells
    }
    return;
}

void check_for_win(Board *ptr, int mines)
{
    int i, j, counter = 0; /* number of cells without bombs. At first assigning to zero*/


    for(i = 1; i <= ptr->height; ++i)
        for(j = 1; j <= ptr->width; ++j)
           if(ptr->cells[i][j].bomb==false && ptr->cells[i][j].ch != '-' && ptr->cells[i][j].ch != '!') /*if no bomb. increment*/
             counter++; /* incrementing cells */

      /* if counter equal below equation, it means user found all the cells which does not contain mines*/
    if (counter == (ptr->height*ptr->width) - mines)
    {
        win = true;
        for(i = 1; i <= ptr->height; ++i)
            for(j = 1; j <= ptr->width; ++j)
               if(ptr->cells[i][j].bomb == true) /* if there is a bomb */
                  ptr->cells[i][j].ch = '*'; // show all the bombs
               else
                  ptr->cells[i][j].ch = ptr->cells[i][j].number_of_mines + '0'; // showing numbers in the cells

        print_board(ptr);
        printf("\nYou Won, Congratulations!!!\n");
          return;
    }
}


void play_game()
{

    srand(time(NULL)); // set seed for rand() in the "bombplacing_randomly" function

    printf("\t\t\t\t ***WELCOME TO MINEWSWEEPER GAME*** \n");
    int x, y, row, column, mines;
    char op;

    printf("Please enter the size of board:\n");
    scanf("%d%d", &x, &y);

    printf("Please enter the number of mines: ");
    scanf("%d", &mines);

    Board *ptr=(Board*)malloc(sizeof(Board)); /* creating dynamic array */
    ptr->height = x;
    ptr->width = y;

    make_board(ptr);
    bombplacing_randomly(ptr,mines);
    numof_adjacent_mines(ptr);

    do
    {
        print_board(ptr);

        printf("Would you like to uncover or mark?  'u' or 'm' ");
        scanf(" %c", &op);
        fflush(stdin); // clearing buffer

        printf("Enter the row number: ");
        scanf("%d", &row);
        printf("Enter the column number: ");
        scanf("%d", &column);

        if(op == 'u') /* u -> uncover */
            uncover(ptr,row,column);
        if(op == 'm') /* m -> mark*/
            ptr->cells[row][column].ch = '!';
        if (!lose) check_for_win(ptr,mines);
    } while(!lose && !win);

     /* memory releasing */
    for(int i = 0; i <= ptr->height+1; ++i)
            free(ptr->cells[i]); /* free each cell */
         free(ptr->cells); /* free array of pointers */
    return;
}
