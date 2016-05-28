#ifndef _JOBG_CPP_
#define _JOBG_CPP_

//Job Gomez
//hw3

/* buildAlphaData function 
	sets values to an image's height and width
   job opengl 
	initiate the values of the image and the
	texture of the image
   job check keys 
	checks whether the player moved left or right
	(up and down as well)
	depending on what key is pressed, it will use
	a different image to simulate the character's
	movement.
*/

#include "game.h"
#include "game_objects.h"
#include "jobG.h"
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <stdio.h>
#include <iostream>
#include "mtime.h"
#include "ppm.h"
#include <stdlib.h>
#include <cmath>
#include <string>
using namespace std;
int width, height;
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
		if (a == 255 && b == 255 && c == 255) {
			*(ptr+0) = a;
			*(ptr+1) = b;
			*(ptr+2) = c;
			*(ptr+3) = (0);
		} else {
			*(ptr+0) = a;
			*(ptr+1) = b;
			*(ptr+2) = c;
			*(ptr+3) = (1);
		}
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void job_opengl(Ppmimage *personImage, GLuint personTexture)
{
	
	//Loading images -- commented out while looking for sprite
//	personImage = ppm6GetImage(img);

	
	//create opengl texture elements
	//glBindTexture(GL_TEXTURE_2D,0);
	//glGenTextures(10, &personTexture);
	//glGenTextures(1, &personTexture[i]);	
	//person
	//int w = personImage->width;
	//int h = personImage->height;
	/*glBindTexture(GL_TEXTURE_2D, personTexture);
	//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *personData = buildAlphaData(personImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 64, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, personData);
	free(personData);*/
	//

	glBindTexture(GL_TEXTURE_2D, personTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *personData = buildAlphaData(personImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 128, 64, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, personData);
	
	free(personData);
}


void job_keys (int key, int &done, Person person, int &people) 
{
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
void res(int w, int h)
{
    width = w;
    height = h;
}
int scroll1 = width + height;
struct timespec bouldersCurrent1, bouldersStart1;
struct timespec totCurrent1, totStart1;
struct timespec logoCurrent1, logoStart1;
struct timespec enterCurrent1, enterStart1;
struct timespec optionsCurrent1, optionsStart1;
struct timespec characterCurrent1, characterStart1;
double bouldersSpan1 = 0.0;
double logoSpan1 = 0.0;
double enterSpan1 = 0.0;
double optionsSpan1 = 0.0;
double characterSpan1 = 0.0;
int fallingBouldersTimer1 = 1;	
int posLogo1[3] = {0, -50, 0};
int posEnter1[3] = {width/2, 0, 0};
double scale1[3] = {1.0f, 1.0f, 0};
double scalePos1[3] = {0, 0, 0};
int pos1[3] = {0, height, 0};
int posOptions1[3] = {width/2+60, 0, 0};
int character1[3] = {0, 0, 0};
int arrow1[3] = {0, 0, 0};

int renderWinCondition(GLuint introTextures[], Ppmimage *introImages[], int enterPressed, int downPressed, int upPressed)
{
	

    	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Background
	float w = introImages[0]->width;
	float h = introImages[0]->height;
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, introTextures[0]);
	glTranslatef(-scale1[0]*625 +625, -scale1[1]*354+354, 0);
	glScalef(scale1[0], scale1[1], scale1[2]);
	
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(0, h + 96);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(w, h + 96);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(w, 96);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(0, 96);

	glEnd();
	glPopMatrix();
	//logo
	if (scroll1 <= -1800) {
                w = introImages[2]->width;
                h = introImages[2]->height;

                glPushMatrix();
                glTranslatef(posLogo1[0], posLogo1[1], posLogo1[2]);

                glBindTexture(GL_TEXTURE_2D, introTextures[2]);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex2f(235, 900);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(w + 235, 900);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(w + 235, h + 294);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(235, h + 294);

                glEnd();
                glPopMatrix();
                glDisable(GL_ALPHA_TEST);

                //Enter Maze
                w = 315 + introImages[3]->width/2;
                h = introImages[3]->height/2;
                glPushMatrix();
                glTranslatef(posEnter1[0], posEnter1[1], posEnter1[2]);

                glBindTexture(GL_TEXTURE_2D, introTextures[3]);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex2f(315 + width/2, height/2);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(width/2 + w, height/2);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(width/2 + w, height/2 - h);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(315 + width/2, height/2 - h);

                glEnd();
                glDisable(GL_ALPHA_TEST);
                glPopMatrix();
		
		
                //Options
                w = 275 + introImages[4]->width/2;
                h = -60 - introImages[4]->height/2;
                glPushMatrix();
                glTranslatef(posOptions1[0], posOptions1[1], posOptions1[2]);

                glBindTexture(GL_TEXTURE_2D, introTextures[4]);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex2f(width/2 + 275, height/2 - 60);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(width/2 + w, height/2 - 60);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(width/2 + w, height/2 + h);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(width/2 + 275, height/2 + h);

                glEnd();
                glDisable(GL_ALPHA_TEST);
                glPopMatrix();

                //Arrow
                w = 250 + introImages[5]->width/1.5;
                h = -5 + introImages[5]->height/1.5;
                glPushMatrix();
                glTranslatef(arrow1[0], arrow1[1], arrow1[2]);

                glBindTexture(GL_TEXTURE_2D, introTextures[5]);
                glEnable(GL_ALPHA_TEST);
                glAlphaFunc(GL_GREATER, 0.0f);
                glBegin(GL_QUADS);

                glTexCoord2f(0.0f, 0.0f); glVertex2f(width/2 + 250, height/2 + 5);
                glTexCoord2f(1.0f, 0.0f); glVertex2f(width/2 + w, height/2 + 5);
                glTexCoord2f(1.0f, 1.0f); glVertex2f(width/2 + w, height/2 - h);
                glTexCoord2f(0.0f, 1.0f); glVertex2f(width/2 + 250, height/2 - h);

                glEnd();
                glDisable(GL_ALPHA_TEST);
                glPopMatrix();	
		
		if (downPressed) {
                        if (arrow1[0] == 0) {
                                arrow1[0] = 20;
                                arrow1[1] = -60;
                        }
                }
                else if (upPressed) {
                        if (arrow1[0] == 20) {
                                arrow1[0] = 0;
                                arrow1[1] = 0;
                        }
                }	
	}
	//boulders
        if (fallingBouldersTimer1 == 1) {
                clock_gettime(CLOCK_REALTIME, &totStart1);
                fallingBouldersTimer1 = 0;
        }
        if (bouldersSpan1 > 6) {
                bouldersSpan1 = 0.0;
                clock_gettime(CLOCK_REALTIME, &bouldersStart1);
        }
        if (logoSpan1 > .8) {
                logoSpan1 = 0.0;
                clock_gettime(CLOCK_REALTIME, &logoStart1);
        }
        if (enterSpan1 > .5) {
                enterSpan1 = 0.0;
                clock_gettime(CLOCK_REALTIME, &enterStart1);
        }
        if (optionsSpan1 > 1) {
                optionsSpan1 = 0.0;
                clock_gettime(CLOCK_REALTIME, &optionsStart1);
        }
	
	w = 50 + introImages[1]->width;
        h = introImages[1]->height;
        glPushMatrix();
        glTranslatef(pos1[0], pos1[1], pos1[2]);

        glBindTexture(GL_TEXTURE_2D, introTextures[1]);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.0f);
        glBegin(GL_QUADS);

        glTexCoord2f(0.0f, 0.0f); glVertex2f(-50, height + h);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(w, height + h);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(w, height);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-50, height);

        glEnd();
        glDisable(GL_ALPHA_TEST);
        glPopMatrix();

        clock_gettime(CLOCK_REALTIME, &bouldersCurrent1);
        bouldersSpan1 += timeDiff(&bouldersStart1, &bouldersCurrent1);

        if (scroll1  > -height*3 && bouldersSpan1 > 6) {
                scroll1 -=100;
                pos1[1] = scroll1;
        }

        if (scroll1 == -1700) {
                scroll1 = -1800;
                clock_gettime(CLOCK_REALTIME, &totCurrent1);
        }

        if (enterPressed && arrow1[0] == 0) {
                clock_gettime(CLOCK_REALTIME, &logoCurrent1);
                logoSpan1 += timeDiff(&logoStart1, &logoCurrent1);
                clock_gettime(CLOCK_REALTIME, &enterCurrent1);
                enterSpan1 += timeDiff(&enterStart1, &enterCurrent1);
                clock_gettime(CLOCK_REALTIME, &optionsCurrent1);
                optionsSpan1 += timeDiff(&optionsStart1, &optionsCurrent1);

                if (posLogo1[1] < 6000 && logoSpan1 > .8) {
                        posLogo1[1] += 25;
                }

                if (posLogo1[1] > 800) {
                        scale1[0] += .00375; scalePos1[0] -= .00375;
                        scale1[1] += .00375; scalePos1[1] -= .00375;
			cout << scale1[1] << endl;
                }

                if (posLogo1[1] == 1800) {
                        return 0;
                }

                if (fabs(posEnter1[0]) < width && enterSpan1 > .5) {
                        posEnter1[0] -= 25;
                }

                if (posOptions1[0] < width && optionsSpan1 > 1) {
                        posOptions1[0] += 25;
                }
	}
	return 1;	
}

#endif
