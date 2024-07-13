#ifndef PORJECTTILE_H
#define PORJECTTILE_H

#include "Object.h"

class Projectile : public Object
{
	float direction[2] = { 0, 0 };

	bool enhanced;

	float damage;
	float speed;

public:
	Projectile(int, int, int, int, int, int, bool);

	~Projectile();

	void move(double);

	void set_enhanced(bool);
	bool get_enhanced();

	void set_direction(int, float);
	float get_direction(int);

	void set_damage(int);
	float get_damage();

	void set_speed(float);
	float get_speed();
};

#endif