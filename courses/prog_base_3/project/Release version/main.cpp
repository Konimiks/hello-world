#include "game.h"

int main(void){
    //Style::Fullscreen
    RenderWindow window(VideoMode (1366, 768), "Chaos Knight Game");
    gameRunning(window);
    return 0;
}
