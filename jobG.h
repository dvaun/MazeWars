#ifndef _JOBG_H_
#define _JOBG_H_

//Job Gomez
#include "ppm.h"
#include "defs.h"
#include <GL/glx.h>
#include "person.h"
/*struct Person {
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
};*/

void job_opengl(Ppmimage *personImage, GLuint personTexture);
void job_keys(int, int &quit, Person person, int &people);


#endif

