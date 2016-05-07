#ifndef WEAPONS_H
#define WEAPONS_H

#include <ctime>
#include "game.h"

struct Weapon{
    Vec dir;
    Vec pos;
    Vec vel;
    float angle;
    Weapon(){
	VecZero(dir);
        pos[0] = (Flt)(40);
        pos[1] = (Flt)(40);
        pos[2] = 0.0f;
        VecZero(vel);
        angle = 0.0;
    }
};

struct Bullet {
    Stats stats;
	//Vec gpos;
	Vec vel;
	float speed;
	float color[3];
	struct timespec time;
	struct Bullet *prev;
	struct Bullet *next;
	Bullet() {
		prev = NULL;
		next = NULL;
	}
	void operator=(Bullet x) {
		stats.gpos[0] = x.stats.gpos[0];
		stats.gpos[1] = x.stats.gpos[1];
		vel[0] = x.vel[0];
		vel[1] = x.vel[1];
		color[0] = x.color[0];
		color[1] = x.color[1];
		color[2] = x.color[2];
		time = x.time;
	}
	void operator=(Weapon x) {
		stats.gpos[0] = x.pos[0];
		stats.gpos[1] = x.pos[1];
		vel[0] = x.vel[0];
		vel[1] = x.vel[1];
	}
};

struct Game {
	Player Player_1;
	Weapon gun;
	Bullet *barr;
	int g_xres;
	int g_yres;
	int nbullets;
	int score = 0;
	gblock **blocks;
	gblock_info game_info;
	struct timespec bulletTimer;
	Game() {
		blocks = NULL;
		barr = new Bullet[MAX_BULLETS];
		nbullets = 0;
		g_xres = 1250;
		g_yres = 900;
	}
};

#endif
