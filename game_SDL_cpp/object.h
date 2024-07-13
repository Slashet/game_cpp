#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
class Object
{
protected:
	SDL_Texture* texture;
    SDL_Surface* surface;
    int colorR, colorG, colorB, colorA;
public:
    SDL_Rect imgRectangle;
    SDL_Rect posRectangle;

    Object();
    
    Object(int, int, int, int, int);
    Object(int, int, int, int, int, int, int, int);

    ~Object();


    void add_rect(int, int, int, int, int);
    void set_texture(SDL_Renderer *, const char imgAdress[50]);
    void draw(SDL_Renderer *, bool, bool);
    void draw_pixel(SDL_Renderer*);
    void clear();

    void set_color(int, int, int, int);
    int get_color(int);

    void set_rect(int, int, int, int, int);
    SDL_Rect get_rect(int);
};

#endif