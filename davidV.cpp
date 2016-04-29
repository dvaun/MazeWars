// Lab 5
// David Vaughan
// 04/28/2016

#ifndef DRAW_F
#define DRAW_F

#include "davidV.h"
#include <GL/glx.h>
#include "Weapon.h"
#include "game.h"

void drawSquare(Object *s, int red, int blue, int green)
{
	glColor3ub(red, blue, green);
	glPushMatrix();
	glTranslatef(s->center[0], s->center[1], s->center[2]);
	glBegin(GL_QUADS);
		glVertex2i(-s->width, -s->height);
		glVertex2i(-s->width, s->height);
		glVertex2i(s->width, s->height);
		glVertex2i(s->width, -s->height);
	glEnd();
	glPopMatrix();
}

void drawParticle(Particle *p, int red, int blue, int green)
{
	glColor3ub(red, blue, green);
	glPushMatrix();
	glTranslatef(p->s.center[0], p->s.center[1], p->s.center[2]);
	glBegin(GL_QUADS);
		glVertex2i(-p->s.width, -p->s.height);
		glVertex2i(-p->s.width, p->s.height);
		glVertex2i(p->s.width, p->s.height);
		glVertex2i(p->s.width, -p->s.height);
	glEnd();
	glPopMatrix();
}

void drawBullet(Bullet *b, float red, float blue, float green)
{
	glColor3f(red, blue, green);
	glBegin(GL_POINTS);
	glVertex2f(b->pos[0], b->pos[1]);
	glVertex2f(b->pos[0]-1.0f, b->pos[1]);
	glVertex2f(b->pos[0]+1.0f, b->pos[1]);
	glVertex2f(b->pos[0], b->pos[1]-1.0f);
	glVertex2f(b->pos[0], b->pos[1]+1.0f);
	glColor3f(red - 0.2f, blue - 0.2f, green - 0.2f);
	glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
	glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
	glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
	glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
	glEnd();
}


// Cameron wrote this player render code w/Gordons
// ship as the temporary player - I've 
// basically put it into it's own draw function

void drawPlayer(Player p)
{
	glColor3fv(p.color);
	glPushMatrix();
	glTranslatef(p.pos[0], p.pos[1], p.pos[2]);
	glRotatef(p.angle, 0.0f, 0.0f, 1.0f);
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

#endif
