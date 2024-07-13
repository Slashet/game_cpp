#include "Projectile.h"

#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Projectile::Projectile(int height, int width, int damage_, int speed_, int X, int Y, bool enhanced_){
	damage = damage_;
	speed = speed_;

	enhanced = enhanced_;


	direction[0] = X * (5 / sqrt(pow(X, 2) + pow(Y, 2)));
	direction[1] = -Y * (5 / sqrt(pow(X, 2) + pow(Y, 2)));
	
	posRectangle = { 350 ,350 , width, height };

	if (enhanced) set_color(204, 85, 0, 255);
	else set_color(255, 255, 255, 255);
}
Projectile::~Projectile() {

}

void Projectile::move(double fpsMultiplier) {

	posRectangle.x += speed * direction[0] * fpsMultiplier;
	posRectangle.y += speed * direction[1] * fpsMultiplier;


}

void Projectile::set_enhanced(bool enhanced_) {
	enhanced = enhanced_;
}
bool Projectile::get_enhanced() {
	return enhanced;
}

void Projectile::set_direction(int whichOne, float direct) {
	if (whichOne == 0 || whichOne == 1)
		direction[whichOne] = direct;
	else
		std::cout << "Invalid set direction [projectiles]" << std::endl;
}
float Projectile::get_direction(int whichOne) {
	if (whichOne == 0 || whichOne == 1)
		return direction[whichOne];
	else {
		std::cout << "Invalid get direction [projectiles]" << std::endl;
		return 0;
	}
}

void Projectile::set_damage(int damage_){
	damage = damage_;
}
float Projectile::get_damage() {
	return damage;
}

void Projectile::set_speed(float speed_) {
	damage = speed_;
}
float Projectile::get_speed() {
	return speed;
}

