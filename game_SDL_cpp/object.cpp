#include "Object.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Object::Object() {
    set_color(255, 255, 255, 255);
}

// 1 - İmage Rectangle || 2 - Position Rectangle 
Object::Object(int whichOne, int rectX, int rectY, int rectWidth, int rectHeight) {
    set_color(255, 255, 255, 255);
    
    switch (whichOne)
    {
    case 1:
        imgRectangle = { rectX ,rectY , rectWidth, rectHeight };
        break;
    case 2:
        posRectangle = { rectX ,rectY , rectWidth, rectHeight };
        break;
    }
}

Object::Object(int imgRectWidth, int imgRectHeight, int imgRectX, int imgRectY, int posRectWidth, int posRectHeight, int posRectX, int posRectY) {
    set_color(255, 255, 255, 255);

    imgRectangle = { imgRectWidth, imgRectHeight, imgRectX, imgRectY };
    posRectangle = { posRectWidth, posRectHeight, posRectX, posRectY };
}

Object::~Object() {
    
}


void Object::add_rect(int whichOne, int rectX, int rectY, int rectWidth, int rectHeight) {
    switch (whichOne)
    {
    case 1:
        imgRectangle = { imgRectangle.x + rectX, imgRectangle.y + rectY, imgRectangle.w + rectWidth, imgRectangle.h + rectHeight };
        break;
    case 2:
        posRectangle = { posRectangle.x + rectX, posRectangle.y + rectY, posRectangle.w + rectWidth, posRectangle.h + rectHeight };
        break;
    }
}
void Object::set_texture(SDL_Renderer* renderer, const char imgAdress[50]) {
    surface = IMG_Load(imgAdress);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
}
void Object::draw(SDL_Renderer* renderer, bool forIMG, bool forPOS)  {
    if (forIMG && forPOS) {
        SDL_RenderCopy(renderer, texture, &imgRectangle, &posRectangle);
    }

    else if (!forIMG && !forPOS) {
        SDL_RenderCopy(renderer, texture, NULL, NULL);
    }

    else if (forIMG) {
        SDL_RenderCopy(renderer, texture, &imgRectangle, NULL);
    }

    else if (forPOS) {
        SDL_RenderCopy(renderer, texture, NULL, &posRectangle);
    }

    clear();
}
void Object::draw_pixel(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, colorR, colorG, colorB, colorA);
    SDL_RenderFillRect(renderer, &posRectangle);
}
void Object::clear() {
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void Object::set_color(int R, int G, int B, int A) {
    colorR = R;
    colorG = G;
    colorB = B;
    colorA = A;
}
int Object::get_color(int whichOne) {
    switch (whichOne)
    {
    case 1:
        return colorR;
        break;
    case 2:
        return colorG;
        break;
    case 3:
        return colorB;
        break;
    case 4:
        return colorA;
        break;
    }
}

void Object::set_rect(int whichOne, int rectX, int rectY, int rectWidth, int rectHeight) {
    switch (whichOne) {
    case 1:
        imgRectangle = { rectX, rectY, rectWidth, rectHeight };
        break;
    case 2:
        posRectangle = { rectX, rectY, rectWidth, rectHeight };
        break;
    }
}
SDL_Rect Object::get_rect(int whichOne) {
    switch (whichOne) {
    case 1:
        return imgRectangle;
        break;
    case 2:
        return posRectangle;
        break;
    }
}