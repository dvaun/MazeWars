/* Name: Matthew Gaitan
 * Date: April 27, 2016
 * Last Modified: May 11, 2016
 * Description: My code handles all of the character movement if a controller 
 * is being used. In the main mazewars.cpp file, the current values for the
 * buttons as well as joysticks are added to an array and those values are
 * later passed to my checkController function. My checkController function
 * does whatever action that relates to the button or joystick being updated.
 * My code also takes a character sprite sheet passed to it (assuming two 
 * frames) and renders it on the screen swapping through the textures if there
 * is movement.
 */

#include "game_objects.h"
#include "joystick.hh"
#include "person.h"
#include "mtime.h"
#include <cmath>
#include <GL/glx.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;

typedef struct crosshair {
		float angle;
} Crosshair;

Crosshair crosshair;

int xwidth, yheight;

void getJoystickEvent(JoystickEvent event, int joy[], int axis[]) 
{
	int number = event.number;
	if (event.type == 0x01) {
		if (joy[number] == 0)
			joy[number] = 1;
		else
			joy[number] = 0;
	}

	if (event.type == 0x02) {
		float value = event.value;
		if (fabs(value) / (float) event.MAX_AXES_VALUE < .2)
			axis[number] = 0;
		else
			axis[number] = value;
	}
}

void movement(Game *g) 
{
	Flt rad = ((g->Player_1.stats.angle+90.0f) / 360.0f) * M_PI * 2.0f;

	Flt xdir = cos(rad);
	Flt ydir = sin(rad);	

	g->Player_1.stats.vel[0] = xdir*2.0f;
	g->Player_1.stats.vel[1] = ydir*2.0f;
}

//new checkController now with no deadzones and easy to read angles
void checkController(int axis[], Game *g) 
{ 
	if (axis[1] || axis[0]) {
		float angle = atan2(axis[1], -axis[0]) / M_PI*180 + 180;
		cout << angle << endl;
		if (angle >= 337.5 || angle <= 22.5 ) 
			g->Player_1.stats.angle = 270;	

		else if (angle > 22.5 && angle <= 67.5) 
			g->Player_1.stats.angle = -45;

		else if (angle > 67.5 && angle <= 112.5) 
			g->Player_1.stats.angle = 0;

		else if (angle > 112.5 && angle <= 157.5) 
			g->Player_1.stats.angle = 45;

		else if (angle > 157.5 && angle <= 202.5) 
			g->Player_1.stats.angle = 90;

		else if (angle > 202.5 && angle <= 247.5) 
			g->Player_1.stats.angle = 135;

		else if (angle > 247.5 && angle <= 292.5) 
			g->Player_1.stats.angle = 180;

		else if (angle > 292.5 && angle <=337.5) 
			g->Player_1.stats.angle = 225;

		movement(g);
	}
}

void renderCrosshair(int axis[], Game *g, bool keyboard) 
{
	int radius = 40;
	int playerX = g->Player_1.stats.spos[0]+1;
	int playerY = g->Player_1.stats.spos[1]+2;

	//Draw Crosshair for aiming
	if (keyboard == false) 
		crosshair.angle = atan2(axis[4], -axis[3]) / M_PI*180 + 180;
	else {
		if (axis[XK_q]) {
			crosshair.angle += .1f;
		}
		if (axis[XK_e]) {
			crosshair.angle -= .1f;
		}
	}	

	float xComponent = radius * cos(crosshair.angle*M_PI/180);
	float yComponent = radius * sin(crosshair.angle*M_PI/180);

	glColor3f(.3f, 1.0f, .3f);

	//create a 30px tall & wide crosshair centered on edge of circle
	glBegin(GL_LINES);	
	glVertex2i(xComponent + playerX, playerY + yComponent - 15);
	glVertex2i(xComponent + playerX, playerY + yComponent + 15);
	glVertex2i(xComponent + playerX - 15, yComponent + playerY);
	glVertex2i(xComponent + playerX + 15, yComponent + playerY);
	glEnd();
}

void renderShield(Game *g) 
{
	int radius = 40;
	int playerX = g->Player_1.stats.spos[0]+1;
	int playerY = g->Player_1.stats.spos[1]+2;

	glColor3f(0.0f, 0.0f, 1.0f);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POINTS);
	for (float a = 0.0; a <= 2*M_PI; a+=0.001) 
		glVertex2f(radius * cos(a) + playerX, radius * sin(a) + playerY);

	glEnd();
}

//montage name-?.png name-??.png -tile 16x16 -geometry 64x64+0+0 -background 
//transparent name.png

Ppmimage* characterSelection(std::string characterColor) 
{
	if (characterColor.compare("red") == 0) {
		return ppm6GetImage((char*)"images/red.ppm");
		std::cout << "Red selected" << std::endl;
	}
	else {
		return ppm6GetImage((char*)"images/blue.ppm");
		std::cout << "Blue selected" << std::endl;
	}
}

struct timespec animationCurrent, animationStart;
double animationSpan = 0.0;
void renderCharacter(Person person, Game *g, float w, int keys[], 
	GLuint personTexture1)
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	glPushMatrix();
	glTranslatef(person.pos[0], person.pos[1], person.pos[2]);	
	glRotatef(g->Player_1.stats.angle, 0, 0, 1.0f);
	glBindTexture(GL_TEXTURE_2D, personTexture1);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);

	glBegin(GL_QUADS);	
	if (animationSpan >= 90) {
		animationSpan = 0.0;
		clock_gettime(CLOCK_REALTIME, &animationStart);
	}
	w /= 2;
	//glBindTexture(GL_TEXTURE_2D, spriteTexture);
	if ((keys[XK_w] || keys[XK_s]) && animationSpan < 12.5) {
			glTexCoord2f(0.66f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(w, w);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(w, -w);
			glTexCoord2f(0.66f, 1.0f); glVertex2f(-w, -w);
	}
	else if((keys[XK_w] || keys[XK_s]) && animationSpan < 45)
	{
			glTexCoord2f(0.33f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(0.66f, 0.0f); glVertex2f( w, w);
			glTexCoord2f(0.66f, 1.0f); glVertex2f( w, -w);
			glTexCoord2f(0.33f, 1.0f); glVertex2f(-w,-w);
	}
	else if((keys[XK_w] || keys[XK_s]) && animationSpan < 67.5)
	{
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(0.33f, 0.0f); glVertex2f( w, w);
			glTexCoord2f(0.33f, 1.0f); glVertex2f( w, -w);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-w,-w);
	}
	else
	{
			glTexCoord2f(0.33f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(0.66f, 0.0f); glVertex2f( w, w);
			glTexCoord2f(0.66f, 1.0f); glVertex2f( w, -w);
			glTexCoord2f(0.33f, 1.0f); glVertex2f(-w,-w);
	}
	
	clock_gettime(CLOCK_REALTIME, &animationCurrent);
	animationSpan += timeDiff(&animationStart, &animationCurrent);
	
	//cout << animationSpan << endl;	

	glEnd();
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}

void resolution(int width, int height)
{
	xwidth = width;
	yheight = height;
}

int scroll = yheight+yheight;
struct timespec bouldersCurrent, bouldersStart;
struct timespec totCurrent, totStart;
struct timespec logoCurrent, logoStart;
struct timespec enterCurrent, enterStart;
struct timespec optionsCurrent, optionsStart;
double bouldersSpan = 0.0;
double logoSpan = 0.0;
double enterSpan = 0.0;
double optionsSpan = 0.0;
int fallingBouldersTimer = 1;
double scale[3] = {1.0f, 1.0f, 0};
double scalePos[3] = {0, 0, 0};
int pos[3] = {0, yheight, 0};
int posLogo[3] = {0, -50, 0};
int posEnter[3] = {xwidth/2, 0, 0};
int posOptions[3] = {xwidth/2+60, 0, 0};

int renderTitleScreen(GLuint introTextures[], Ppmimage *introImages[], 
	int enterPressed)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//set background to black to give cenematic feel
	glClearColor(0.0, 0.0, 0.0, 0.0);
	
	//Background
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, introTextures[0]);
	glTranslatef(-scale[0]*625 +625, -scale[1]*354+354, 0);
	glScalef(scale[0], scale[1], scale[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, introImages[0]->height+96);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(introImages[0]->width, 
		introImages[0]->height+96);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(introImages[0]->width, 96);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 96);

	glEnd();
	glPopMatrix();
	//MazeWars Logo
	if (scroll <= -1800) {
		glPushMatrix();
		glTranslatef(posLogo[0], posLogo[1], posLogo[2]);

		glBindTexture(GL_TEXTURE_2D, introTextures[2]);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(235, 900);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(introImages[2]->width+235, 900);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(introImages[2]->width+235, 
			introImages[2]->height+294);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(235, introImages[2]->height+294);
		glEnd();
		glPopMatrix();
		glDisable(GL_ALPHA_TEST);

		//Enter Maze
		glPushMatrix();
		glTranslatef(posEnter[0], posEnter[1], posEnter[2]);

		glBindTexture(GL_TEXTURE_2D, introTextures[3]);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(xwidth/2, yheight/2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(xwidth/2 + 
			introImages[3]->width/2, yheight/2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(xwidth/2 + 
			introImages[3]->width/2, yheight/2-introImages[3]->height/2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(xwidth/2, 
			yheight/2-introImages[3]->height/2);

		glEnd();
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		//Options
		glPushMatrix();
		glTranslatef(posOptions[0], posOptions[1], posOptions[2]);

		glBindTexture(GL_TEXTURE_2D, introTextures[4]);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(xwidth/2 + 25, yheight/2 - 60);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(xwidth/2 + 25 + 
			introImages[4]->width/2, yheight/2 - 60);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(xwidth/2 + 25 + 
			introImages[4]->width/2, yheight/2 - 60 - 
			introImages[4]->height/2);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(xwidth/2 + 25, yheight/2 - 60 - 
			introImages[4]->height/2);

		glEnd();
		glDisable(GL_ALPHA_TEST);
		glPopMatrix();

		//Arrow
		/*glBindTexture(GL_TEXTURE_2D, introTextures[5]);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0f, 0.0f); glVertex2f(xwidth/2 - 25, yheight/2);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(xwidth/2 - 25 + 
			introImages[5]->width, yheight/2);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(xwidth/2 - 25 + 
			introImages[5]->width, yheight/2 - introImages[5]->height);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(xwidth/2 - 25, yheight/2 - 
			introImages[5]->height);
		
		glEnd();
		glDisable(GL_ALPHA_TEST);
		glPopMatrix(); */
	}

	//Falling Boulders
	if (fallingBouldersTimer == 1) {
		clock_gettime(CLOCK_REALTIME, &totStart);
		fallingBouldersTimer = 0;
	}
	if (bouldersSpan > 6) {
		bouldersSpan = 0.0;
		clock_gettime(CLOCK_REALTIME, &bouldersStart);
	}
	if (logoSpan > .8) {
		logoSpan = 0.0;
		clock_gettime(CLOCK_REALTIME, &logoStart);
	}
	if (enterSpan > .5) {
		enterSpan = 0.0;
		clock_gettime(CLOCK_REALTIME, &enterStart);
	}
	if (optionsSpan > 1) {
		optionsSpan = 0.0;
		clock_gettime(CLOCK_REALTIME, &optionsStart);
	}

	glPushMatrix();
	glTranslatef(pos[0], pos[1], pos[2]);

	glBindTexture(GL_TEXTURE_2D, introTextures[1]);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(-50, yheight+introImages[1]->height);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(introImages[1]->width+50, 
		yheight+introImages[1]->height);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(introImages[1]->width+50, yheight);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-50, yheight);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();

	clock_gettime(CLOCK_REALTIME, &bouldersCurrent);
	bouldersSpan += timeDiff(&bouldersStart, &bouldersCurrent);

	if (scroll  > -yheight*3 && bouldersSpan > 6) {
		scroll -=100;
		pos[1] = scroll;
	}

	if (scroll == -1700) {
		scroll = -1800;
		clock_gettime(CLOCK_REALTIME, &totCurrent);
	}

	if (enterPressed) {
		clock_gettime(CLOCK_REALTIME, &logoCurrent);
		logoSpan += timeDiff(&logoStart, &logoCurrent);
		clock_gettime(CLOCK_REALTIME, &enterCurrent);
		enterSpan += timeDiff(&enterStart, &enterCurrent);
		clock_gettime(CLOCK_REALTIME, &optionsCurrent);
		optionsSpan += timeDiff(&optionsStart, &optionsCurrent);

		if (posLogo[1] < 6000 && logoSpan > .8) {
			posLogo[1] += 25;
		}
		
		if (posLogo[1] > 800) {
				scale[0] += .00375; scalePos[0] -= .00375;
				scale[1] += .00375; scalePos[1] -= .00375;
				cout << scale[1] << endl;
		}

		if (posLogo[1] == 1800) {
			return 0;
		}

		if (fabs(posEnter[0]) < xwidth && enterSpan > .5) {
			posEnter[0] -= 25;
		}

		if (posOptions[0] < xwidth && optionsSpan > 1) {
			posOptions[0] += 25;
		}

	}

	return 1;
}
