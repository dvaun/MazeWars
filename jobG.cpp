#ifndef _JOBG_CPP_
#define _JOBG_CPP_

//Job Gomez
//Lab 5
#include "game.h"
#include "jobG.h"
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdio.h>
#include <iostream>
#include "ppm.h"
//defined types

Person person;
Ppmimage *personImage = NULL;
GLuint personTexture;
int npeople = 0;


void job_opengl(void)
{
	//Loading images -- commented out while looking for sprite
	personImage = ppm6GetImage((char*)"./sprite.ppm");
	
	//create opengl texture elements
	glGenTextures(1, &personTexture);
	
	//person
	int w = personImage->width;
	int h = personImage->height;
	
	glBindTexture(GL_TEXTURE_2D, personTexture);
	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0, 0, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 
							personImage->data);
}


void job_keys(int key, int *done){
	switch(key) {
		case XK_Escape:
			*done = 1;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Left:
                        //if (XK_Left) {
			VecCopy(person.pos, person.lastpos);
                        //bigfoot2.pos[0] = bigfoot.pos[0];
                        person.pos[0] -= 10.0;
                        std::cout << "Going left from switch statement\n";
                        //}
                        break;
                case XK_Right:
                        VecCopy(person.pos, person.lastpos);
                        person.pos[0] += 10.0;
                        break;
                case XK_Up:
                        VecCopy(person.pos, person.lastpos);
                        person.pos[1] += 10.0;
                        break;
                case XK_Down:
                        VecCopy(person.pos, person.lastpos);
                        person.pos[1] -= 10.0;
                        break;
	}
}

#endif
