#include "Character.h"
#include "Projectile.h"

#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>



Character::Character() {
	isMain = true;
	
	health = 100;
	damage = 35;
	
	*level = 0;
	*stamina = 100;
	*experience = 0;

	imgRectangle = { 0 ,20 , 40, 40 };
	posRectangle = { 300 ,300 , 120, 120 };
}
Character::Character(const Object& object, float health_, float damage_) {
	isMain = false;

	damage = damage_;
	health = health_;

	delete level;
	delete stamina;
	delete experience;

	imgRectangle = { 0 ,0 , 32, 32 };
	posRectangle = { rand() % 1620 ,rand() % 300 , 96, 96 };
}
Character::Character(std::string) {
	isMain = true;
	delete stamina;
	delete experience;
	delete level;

	direction[1] = 1;
	imgRectangle = { 0 , 20 , 40 , 40 };
	posRectangle = { -3 , 8 , 90 , 90 };
}

void Character::animation(SDL_Renderer* renderer, int whichAnimation, float tick){
	if (isMain) {
		imgRectangle.x = (20 + (80 * static_cast<int>(tick))) % 320;
		if (direction[1] == 1) { imgRectangle.y = 180; }
		else if (direction[1] == -1) { imgRectangle.y = 260; }
		else if (direction[0] == 1) { imgRectangle.y = 20; }
		else if (direction[0] == -1) { imgRectangle.y = 100; }
		
	} 
	else{
		imgRectangle.x = (32 * static_cast<int>(tick * 0.80)) % 128;
		if (direction[1] == -1) { imgRectangle.y = 64; }
		else if (direction[0] == -1) { imgRectangle.y = 0; }
		else if (direction[0] == 1) { imgRectangle.y = 32; }
		else if (direction[1] == 1) { imgRectangle.y = 96; }
	}


	switch (whichAnimation)
	{
	case 0: // main idle

		set_texture(renderer, "src/image/Character/idle.png");
		break;
	case 1: // main walk
		set_texture(renderer, "src/image/Character/walk.png");
		break;
	case 2: // skeleton idle 
		
		set_texture(renderer, "src/image/Skeleton/idle.png");
		break;
	case 3: // skeleton walk
		set_texture(renderer, "src/image/Skeleton/walk.png");
		break;
	default:
		break;
	}
	draw(renderer, 1, 1);
}
void Character::movement(Object &object, double fpsMultiplier) {
	if (direction[0] == -1 && object.imgRectangle.x > 4) { object.imgRectangle.x += -fpsMultiplier * 3; }
	if (direction[0] == 1 && object.imgRectangle.x < 556) { object.imgRectangle.x += fpsMultiplier * 4; }
	if (direction[1] == -1 && object.imgRectangle.y > 0) { object.imgRectangle.y += -fpsMultiplier * 3; }
	if (direction[1] == 1 && object.imgRectangle.y < 308) { object.imgRectangle.y += fpsMultiplier * 4; }
}
void Character::movement(Character &charimo, Object &object, double fpsMultiplier) {
	int dirX = (posRectangle.x - 310);
	int dirY = (posRectangle.y - 310);
	direction[0] = (dirX != 0) ? (dirX / abs(dirX)) : 0;
	direction[1] = (dirY != 0) ? (dirY / abs(dirY)) : 0;

	posRectangle.x -= fpsMultiplier * direction[0] * 2;
	posRectangle.y -= fpsMultiplier * direction[1] * 2;
	
	if (charimo.get_direction(0) == -1 && object.imgRectangle.x > 4) { posRectangle.x -= -fpsMultiplier * (37 / 3); }
	if (charimo.get_direction(0) == 1 && object.imgRectangle.x < 556) { posRectangle.x -= fpsMultiplier * (37 / 3); }
	if (charimo.get_direction(1) == -1 && object.imgRectangle.y > 0) { posRectangle.y -= -fpsMultiplier * (37 / 3); }
	if (charimo.get_direction(1) == 1 && object.imgRectangle.y < 308) { posRectangle.y -= fpsMultiplier * (37 / 3); }

	
}
void Character::proejctile_control(std::vector<Character> * skeletons, SDL_Renderer* renderer, const Object& object, double fpsMultiplier) {
	for (int i = 0; i < projectiles.size(); i++) {
		
		//std::cout << i+1 << "| X: " << projectiles[i].posRectangle.x << " | Y: " << projectiles[i].posRectangle.y << std::endl;
		
		projectiles[i].move(fpsMultiplier);
		projectiles[i].draw_pixel(renderer);
		projectiles[i].posRectangle.x -= direction[0] * 9 * fpsMultiplier;
		projectiles[i].posRectangle.y -= direction[1] * 9 * fpsMultiplier;

		if (object.imgRectangle.x + (projectiles[i].posRectangle.x / 3) > 770 ||
			object.imgRectangle.x + (projectiles[i].posRectangle.x / 3) < 50 ||
			object.imgRectangle.y + (projectiles[i].posRectangle.y / 3) < 50 ||
			object.imgRectangle.y + (projectiles[i].posRectangle.y / 3) > 500)
		{
			projectiles.erase(projectiles.begin() + i);
			break;
		}
	
		for (int j = 0; j < skeletons->size(); j++) {
			if (projectiles[i].posRectangle.x > (*skeletons)[j].posRectangle.x && projectiles[i].posRectangle.x < (*skeletons)[j].posRectangle.x + 96)
				if (projectiles[i].posRectangle.y > (*skeletons)[j].posRectangle.y && projectiles[i].posRectangle.y < (*skeletons)[j].posRectangle.y + 96) {
					if (!projectiles[i].get_enhanced()) {
						(*skeletons)[j].set_health((*skeletons)[j].get_health() - damage);
						
						projectiles.erase(projectiles.begin() + i);
						break;
					}
					else {
						skeletons->erase(skeletons->begin() + j);
						set_experience(get_experience() + 10);
						break;
					}
				}
		}
	}
}



void Character::set_projectile(std::vector<Projectile> proejctiles_) {
	projectiles = proejctiles_;
}
std::vector<Projectile> * Character::get_projectile() {
	return &projectiles;
}


void Character::set_damage(float damage_) {
	damage = damage_;
}
float Character::get_damage() {
	return damage;
}

void Character::set_health(float health_) {
	health = health_;
}
float Character::get_health() {
	return health;
}

void Character::set_level(int level_) {
	*level = level_;
}
int Character::get_level() {
	return *level;
}

void Character::set_experience(float experience_) {
	*experience = experience_;
}
float Character::get_experience() {
	return *experience;
}

void Character::set_stamina(float stamina_) {
	if (isMain)
		*stamina = stamina_;
}
float Character::get_stamina(){
	if (isMain)
		return *stamina;
}

void Character::set_direction(int whichOne, int direct) {
	if (whichOne == 0 || whichOne == 1)
		direction[whichOne] = direct;
	else
		std::cout << "Invalid Set Dirction [Character]" << std::endl;
}
int Character::get_direction(int whichOne) {
	if (whichOne == 0 || whichOne == 1)
		return direction[whichOne];
	else {
		std::cout << "Invalid Get Direction [Character]" << std::endl;
		return 0;
	}
}
