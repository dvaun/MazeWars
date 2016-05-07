#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Power_up.h"
#include "defs.h"
#include "game.h"
#include "davidV.h"
#include <GL/glx.h>

typedef int Explosive;


struct Player {
	Stats stats;
	Vec dir;
	Vec pos;
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
		stats.angle = 0.0;
		//PowerUp type=0 is the default no powerup option
		P_UP[0] = 0;
		P_UP[1] = 0;
		P_UP[2] = 0;
	}
	void draw(float x, float y, float angle) {
		setColor(p.stats);
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

#endif
