#include "myMain.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Room.h"
#include "Game.h"





int myMain()
{
    Game game;
   

    while (game.running())
    {
        game.update();
        game.render();
    }

    return 0;

}

