#ifndef WEAPONS_H
#define WEAPONS_H

#include <ctime>
#include "game.h"
//#include "Player.h"
//#include "davidV.cpp"
#include "Power_up.h"
#include <GL/glx.h>
#include <stdio.h>
#include "textrender.h"

typedef int Explosive;

struct Player {
	Stats stats;
	PowerUp P_UP[3];
	int Max_Health;
	int Current_Health;
	int Current_Ammo = 100;
	int Max_Ammo = 100;
	Explosive P_Secondary;
	Player() {
		Current_Health = 100;
		Max_Health = 100;
		//PowerUp type=0 is the default no powerup option
		P_UP[0] = 0;
		P_UP[1] = 0;
		P_UP[2] = 0;
	}
	void draw(float x, float y, Stats stats) {
		glColor3f((float) stats.color[0],255,(float) \
			stats.color[2]);
		glPushMatrix();
		glTranslatef(stats.spos[0], stats.spos[1], 0);
		glRotatef(stats.angle, 0.0f, 0.0f, 1.0f);
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
		drawWhiteNum(x,y,10,10,x);
		drawWhiteNum(x,y,10,-10,y);
	}
	~Player() {}
};

struct Weapon{
	Stats stats;
	Vec dir;
	float angle;
	Weapon(){
		VecZero(dir);
		stats.gpos[0] = 0;
		stats.gpos[1] = 0;
		VecZero(stats.vel);
		angle = 0.0;
	}
	~Weapon() {}
};

struct Bullet {
	Stats stats;
//Vec gpos;
	Vec vel;
	struct timespec time;
	struct Bullet *prev;
	struct Bullet *next;
	Bullet() {
		stats.color[0] = 255;
		stats.color[1] = 255;
		stats.color[2] = 255;
		stats.width = 1;
		stats.height = 1;
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
		stats.gpos[0] = x.stats.gpos[0];
		stats.gpos[1] = x.stats.gpos[1];
		vel[0] = x.stats.vel[0];
		vel[1] = x.stats.vel[1];
	}
	void draw(float x, float y, Stats stats) {
		printf("x:%f y:%f\n", x, y);
		glColor3f(stats.color[0], stats.color[1],
				stats.color[2]);
		glPushMatrix();
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
		glPopMatrix();
	}
	~Bullet() {}
};

struct Monster {
	Stats stats;
	void draw() {

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
	~Game() {}
};

#endif
