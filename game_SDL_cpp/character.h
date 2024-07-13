#ifndef CHARACTER_h
#define CHARACTER_h

#include "Object.h"
#include "projectile.h"

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Character : public Object
{
	int direction[2] = { 0, 0 };
	bool isMain = 0;

	float damage;
	float health;

	int timer;

	int* level = new int;
	float* experience = new float;
	float* stamina = new float;
	
	std::vector<Projectile> projectiles;

public:
	Character();
	Character(const Object& object, float, float);
	Character(std::string);

	void animation(SDL_Renderer *, int, float);
	void movement(Object &, double);
	void movement(Character &, Object&, double);
	void proejctile_control(std::vector<Character> *, SDL_Renderer *, const Object &, double);


	void set_projectile(std::vector<Projectile>);
	std::vector<Projectile> * get_projectile();

	void set_damage(float);
	float get_damage();

	void set_health(float);
	float get_health();

	void set_level(int);
	int get_level();

	void set_experience(float);
	float get_experience();

	void set_stamina(float);
	float get_stamina();

	void set_direction(int, int);
	int get_direction(int);
};

#endif