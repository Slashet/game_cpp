#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <ctime>

#include "game.h"
#include "object.h"
#include "Character.h"
#include "Projectile.h"

//--------------------------------------------------------------------------------------------

int mouseX, mouseY;
float anim_tick;

Object background(1, 200, 200, 216, 216);
Object cursor(2, 0, 0, 30, 30);
Character mini_char("killMePls");

Object health_bar(2, 35, 40, 100, 10);
Object stamina_bar(2, 35, 55, 100, 10);
Object experience_bar(2, 35, 60, 100, 10);

std::vector<Character> skeletons;
Character charimo;

int enemy_max_number;
int enemy_spawn;

time_t start_time;
int game_time;

//--------------------------------------------------------------------------------------------

void mousePress(SDL_MouseButtonEvent& b);

void gameEvent(SDL_Event event) {
    while (SDL_PollEvent(&event))
    {

        if (event.type == SDL_QUIT) {
            SDL_Quit();
            exit(0);
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            //std::cout << "x: " << mouseX << " | y: " << mouseY << std::endl;
            SDL_GetMouseState(&mouseX, &mouseY);
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            mousePress(event.button);
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_w)    charimo.set_direction(1, -1); 
            if (event.key.keysym.sym == SDLK_s)  charimo.set_direction(1, 1);
            if (event.key.keysym.sym == SDLK_d) charimo.set_direction(0, 1);
            if (event.key.keysym.sym == SDLK_a)  charimo.set_direction(0, -1);
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s)    charimo.set_direction(1, 0);
            if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_a) charimo.set_direction(0, 0);
        }
    }
}

void gameStart() {
    game_time = 1;
    enemy_spawn = game_time;
    anim_tick = 0;
    start_time = std::time(NULL) - 600;
    enemy_max_number = 10;

    health_bar.set_color(255, 0, 0, 255);
    stamina_bar.set_color(0, 255, 197, 255);
    experience_bar.set_color(255, 255, 0, 255);

    SDL_ShowCursor(SDL_DISABLE);
}       

void gameLoop(SDL_Window* window, SDL_Renderer* renderer, double fpsMultiplier) {
    anim_tick += 1 * fpsMultiplier;
    if (anim_tick > 100) { anim_tick = 0; }

    game_time = std::time(NULL) - start_time;

    // Background ----------------------------------------------------------------------------------------------------------

    background.set_texture(renderer, "src/image/Background/bg_two.png");
    background.draw(renderer, 1, 0);

    // Charimo -------------------------------------------------------------------------------------------------------------

    charimo.movement(background, fpsMultiplier);
    charimo.proejctile_control(&skeletons, renderer, background, fpsMultiplier);

    if (charimo.get_stamina() < 101) charimo.set_stamina(charimo.get_stamina() + (fpsMultiplier * (1 + (0.2 * charimo.get_level()))));

    if (charimo.get_direction(0) != 0 || charimo.get_direction(1) != 0) charimo.animation(renderer, 1, anim_tick); 
    else charimo.animation(renderer, 0, anim_tick);
    
    if (charimo.get_experience() > 100 + (10 * charimo.get_level())) 
    {
        charimo.set_level(charimo.get_level() + 1);
        charimo.set_experience(0);
        charimo.set_health(100 + 10 * charimo.get_level());
        charimo.set_damage(charimo.get_damage() + 3);
    }

    if (charimo.get_stamina() >= 100) stamina_bar.set_color(255, 191, 0, 255);
    else stamina_bar.set_color(0, 255, 197, 255);

    // Enemy ---------------------------------------------------------------------------------------------------------------

    enemy_max_number = 10 + charimo.get_level() * 10 + game_time / 60 * 20;

    int* enemy_spawn_time = new int(60 / game_time * charimo.get_level());

    if (enemy_max_number > skeletons.size() && (game_time - enemy_spawn) > *enemy_spawn_time) {
        skeletons.push_back(Character(background, 100, 20));
        enemy_spawn = game_time;
    }
    
    for (int i = 0; i < skeletons.size(); i++) {
        // animation
        if (skeletons[i].get_direction(0) != 0 || skeletons[i].get_direction(1) != 0) skeletons[i].animation(renderer, 3, anim_tick);
        else skeletons[i].animation(renderer, 2, anim_tick);
        
        // giving damage to main character
        if (skeletons[i].posRectangle.x > 290 && skeletons[i].posRectangle.x < 390)
            if (skeletons[i].posRectangle.y > 290 && skeletons[i].posRectangle.y < 390)
            {
                skeletons.erase(skeletons.begin() + i);
                charimo.set_health(charimo.get_health() - skeletons[i].get_damage());
                break;
            }

        // checking is it dead
        if (skeletons[i].get_health() < 0) {
            charimo.set_experience(charimo.get_experience() + 10);
            skeletons.erase(skeletons.begin() + i);
            break;
        }
        
        // movement
        skeletons[i].movement(charimo, background, fpsMultiplier);
    }

    delete enemy_spawn_time;
    // Cursor --------------------------------------------------------------------------------------------------------------

    cursor.set_texture(renderer, "src/image/stuff/cursor.png");
    cursor.draw(renderer, 0, 1);
    cursor.posRectangle.x = mouseX - 10;
    cursor.posRectangle.y = mouseY - 10;

    // ---------------------------------------------------------------------------------------------------------------------

    stamina_bar.set_rect(2, 35, 50, charimo.get_stamina(), 10);
    experience_bar.set_rect(2, 35, 60, (charimo.get_experience() / (100 + (10 * charimo.get_level()))) * 100, 10);
    health_bar.set_rect(2, 35, 40, charimo.get_health(), 10);

    stamina_bar.draw_pixel(renderer);
    health_bar.draw_pixel(renderer);
    experience_bar.draw_pixel(renderer);

    mini_char.animation(renderer, 0, anim_tick);

    // ---------------------------------------------------------------------------------------------------------------------
    if (charimo.get_health() < 0)
        exit(0);
}



void mousePress(SDL_MouseButtonEvent& b) {
    if (b.button == SDL_BUTTON_LEFT) {
        if (charimo.get_stamina() > 15) {
            charimo.get_projectile()->push_back(Projectile(10, 10, 10, 3, mouseX - 350, -mouseY + 350, false));
            charimo.set_stamina(charimo.get_stamina() - 15);
        }
    }
    if (b.button == SDL_BUTTON_RIGHT) {
        if (charimo.get_stamina() > 100) {
            charimo.get_projectile()->push_back(Projectile(10, 10, 10, 10, mouseX - 350, -mouseY + 350, true));
            charimo.set_stamina(charimo.get_stamina() - 100);
        }
    }

}