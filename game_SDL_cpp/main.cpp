#include <iostream>
#include <Windows.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Game.h"



int main(int argc, char *argv[]){
    SDL_SetMainReady();
    
    //SDL initialize
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(IMG_INIT_PNG);
    
    //create the window and render
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    //initialize the window and render
    window = SDL_CreateWindow("2D RPG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 720, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    //event
    SDL_Event windowEvents{};

    //Fps Variables
    unsigned int a = SDL_GetTicks();
    unsigned int b = SDL_GetTicks();
    double delta = 0;
    
    
    gameStart();

    while (true)
    {
        a = SDL_GetTicks();
        delta += a - b;
        if (delta > 1000 / 120.0)
        {
            //std::cout << "fps: " << 1000 / delta << std::endl;
            gameEvent(windowEvents);

            gameLoop(window, renderer, 1 / ((1000 / delta) / 60));

            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
            
            delta = 0;
        }

        b = SDL_GetTicks();
    }
    
	return 0;
}