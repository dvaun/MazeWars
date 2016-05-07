#ifndef WEAPONS_H
#define WEAPONS_H

#include <ctime>
#include "game.h"
#include "Player.h"
#include <GL/glx.h>

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
	struct timespec time;
	struct Bullet *prev;
	struct Bullet *next;
	Bullet() {
		stats.color[0] = 0;
		stats.color[1] = 0;
		stats.color[2] = 0;
		prev = NULL;
		next = NULL;
	}
	void operator=(Bullet x) {
		stats.gpos[0] = x.stats.gpos[0];
		stats.gpos[1] = x.stats.gpos[1];
		vel[0] = x.vel[0];
		vel[1] = x.vel[1];
		time = x.time;
	}
	void operator=(Weapon x) {
		stats.gpos[0] = x.pos[0];
		stats.gpos[1] = x.pos[1];
		vel[0] = x.vel[0];
		vel[1] = x.vel[1];
	}
	void draw(float x, float y) {
		glTranslatef(x,y,0);
		glBegin(GL_POINTS);
			glVertex2f(x, y);
			glVertex2f(x-1.0f, y);
			glVertex2f(x+1.0f, y);
			glVertex2f(x, y-1.0f);
			glVertex2f(x, y+1.0f);
		glColor3f(stats.color[0] - .2f, stats.color[1] - 0.2f,
				stats.color[2] - 0.2f);
			glVertex2f(x-1.0f, y-1.0f);
			glVertex2f(x-1.0f, y+1.0f);
			glVertex2f(x+1.0f, y-1.0f);
			glVertex2f(x+1.0f, y+1.0f);
		glEnd();
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
