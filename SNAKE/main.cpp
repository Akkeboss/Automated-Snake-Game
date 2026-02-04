#include "src/Game.h"
#include <cstdlib>
#include <ctime>
/* 
    Need to check if snake is dead
    Handling so the snake doesnt move through it self because then it dies
*/

int main(){
    srand(time(0));
    Game SnakeGame;
    SnakeGame.run();
}