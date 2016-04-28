#include "game.h"
#include "jobG.h"
//defined types

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, xres, yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	
	//Loading images
	personImage = ppm6GetImage("sprite.ppm");
	
	//create opengl texture elements
	glGenTextures(1, &personTexture);
	
	//person
	int w = personImage->width;
	int h = personImage->height;
	
	glBindTexture(GL_TEXTURE_2D, personTexture);
	//
	glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextImage2D(GL_TEXTURE_2D,0, 0, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, 
							personImage->data);
	
	
}


int check_keys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
	//
	//This code maintains an array of key status values.
	switch(key) {
		case XK_Escape:
			return 1;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Left:
                        //if (XK_Left) {
                            VecCopy(person.pos, person.lastpos) 
				= VecCopy(person.pos, person.lastpos);
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
