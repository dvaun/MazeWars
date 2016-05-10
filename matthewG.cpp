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
		if(axis[1] || axis[0]) {
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
		if(keyboard == false) 
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
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBegin(GL_POINTS);
		for (float a = 0.0; a <= 2*M_PI; a+=0.001) 
		glVertex2f(radius * cos(a) + playerX, radius * sin(a) + playerY);
		
		glEnd();
	}

	// montage name-?.png name-??.png -tile 16x16 -geometry 64x64+0+0 -background 
	// transparent name.png

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

	void renderCharacter(Person person, Game *g, float w, GLuint spriteTexture,
				   		int keys[]) 
	{
		glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
		glPushMatrix();
		glTranslatef(person.pos[0], person.pos[1], person.pos[2]);	
		glRotatef(g->Player_1.stats.angle, 0, 0, 1.0f);
		//glBindTexture(GL_TEXTURE_2D, personTexture1);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);

		glBegin(GL_QUADS);	
		//clock_gettime(CLOCK_REALTIME, &animationCurrent);
		//animationSpan = timeDiff(&animationStart, &animationCurrent);
		glBindTexture(GL_TEXTURE_2D, spriteTexture);
		static int control = 0;
		if(control <= 20 && (keys[XK_w] || keys[XK_s])) {
			glTexCoord2f(0.5f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(1.0f, 0.0f); glVertex2f(w, w);
			glTexCoord2f(1.0f, 1.0f); glVertex2f(w, -w);
			glTexCoord2f(0.5f, 1.0f); glVertex2f(-w, -w);
		}
		else
		{
			glTexCoord2f(0.0f, 0.0f); glVertex2f(-w, w);
			glTexCoord2f(0.5f, 0.0f); glVertex2f( w, w);
			glTexCoord2f(0.5f, 1.0f); glVertex2f( w, -w);
			glTexCoord2f(0.0f, 1.0f); glVertex2f(-w,-w);
		}
		control++;
		control %= 40;
		cout << control << endl;

		glEnd();
		glPopMatrix();
	}

