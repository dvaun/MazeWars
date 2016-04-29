#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Weapon.h"
#include "defs.h"

const int MAX_BULLETS = 4;

struct Game {
	Player Player_1;
	Weapon gun;
	Bullet *barr;
	int nbullets;
	int score = 0;
	struct timespec bulletTimer;
	Game() {
		barr = new Bullet[MAX_BULLETS];
		nbullets = 0;
	}
};

struct Object {
	float width, height;
	float radius;
	Vec center;
	Vec vel;
	Vec pos;
};

struct Particle {
	Object s;
	Vec vel;
	Vec pos;
	float gravity;
};

#endif
