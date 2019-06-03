 /* user header file */
#include "MineSweeper.h"

int main()
{
    clock_t begin = clock(); /* getting time at the beginning */

    play_game();

    clock_t end = clock();  /* getting time at the end */
    double spend_time = (double)(end - begin) / CLOCKS_PER_SEC; /* time difference */

    printf("You spent %.2f seconds playing the game\n", spend_time);
    return 0;
}
