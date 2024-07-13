#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void gameEvent(SDL_Event);


void gameStart();

void gameLoop(SDL_Window *, SDL_Renderer *, double);

#endif