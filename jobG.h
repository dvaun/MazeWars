#ifndef _JOBG_H_
#define _JOBG_H_

//Job Gomez
#include "ppm.h"
#include "defs.h"
#include <GL/glx.h>
/*
typedef float Flt;
typedef float Vec[3];
typedef Flt     Matrix[4][4];
*/

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Person {
	int xres = 1250;
	int yres = 800;
        Vec dir;
        Vec pos;
	Vec lastpos;
        Vec vel;
        float angle;
        float color[3];
        Person() {
                VecZero(dir);
                pos[0] = (Flt)(xres/2);
                pos[1] = (Flt)(yres/2);
                pos[2] = 0.0f;
                VecZero(vel);
                angle = 0.0;
                color[0] = 1.0;
                color[1] = 1.0;
                color[2] = 1.0;
        }
};

/*
Person person;
Ppmimage *personImage = NULL;
GLuint personTexture;
int npeople = 0;

void job_opengl(void);
int job_keys(int);
*/
void job_opengl(void);
void job_keys(int, int*);


#endif

