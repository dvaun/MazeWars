#ifndef WEAPONS_H
#define WEAPONS_H

#include <ctime>
#include "game.h"
//#include "Player.h"
//#include "davidV.cpp"
#include "Power_up.h"
#include <GL/glx.h>

typedef int Explosive;

struct Player {
	Stats stats;
	Vec dir;
	Vec pos;
	float angle;
	PowerUp P_UP[3];
	int Max_Health;
	int Current_Health;
	int Current_Ammo = 100;
	int Max_Ammo = 100;
	Explosive P_Secondary;
	Player() {
		VecZero(dir);
		pos[0] = 625;
		pos[1] = 450;
		pos[2] = 0.0f;
		stats.color[0] = 130;
		stats.color[1] = 240;
		stats.color[2] = 30;
		Current_Health = 100;
		Max_Health = 100;
		angle = 0.0;
		//PowerUp type=0 is the default no powerup option
		P_UP[0] = 0;
		P_UP[1] = 0;
		P_UP[2] = 0;
	}
	void draw(float x, float y, float angle) {
		glColor3f((float) stats.color[0],(float) stats.color[1],(float) \
			stats.color[2]);
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
			glVertex2f(-12.0f, -10.0f);
			glVertex2f(  0.0f,  20.0f);
			glVertex2f(  0.0f,  -6.0f);
			glVertex2f(  0.0f,  -6.0f);
			glVertex2f(  0.0f,  20.0f);
			glVertex2f( 12.0f, -10.0f);
		glEnd();
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
			glVertex2f(0.0f, 0.0f);
		glEnd();
		glPopMatrix();
	}
};

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
