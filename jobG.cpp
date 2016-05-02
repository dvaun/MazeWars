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
#include <stdlib.h>
//defined types

//Person person;
//Ppmimage *personImage = NULL;
//GLuint personTexture;
//int people = 0;

unsigned char *buildAlphaData(Ppmimage *img)
{
	//add 4th component to RGB stream...
	int i;
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		*(ptr+3) = (a|b|c);
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void job_opengl(Ppmimage *personImage, GLuint personTexture)
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(personImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, 
							GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);//personImage->data);
	free(silhouetteData);

}


void job_keys(int key, int &done, Person person, int &people){
	switch(key) {
		case XK_Escape:
			done = 1;
		case XK_t:
			people ^= 1;
			if (people) {
				person.pos[0] = 100;
			}
			break;
		case XK_Left:
			VecCopy(person.pos, person.lastpos);
            person.pos[0] -= 10.0;
            std::cout << "Going left from switch statement\n";
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
