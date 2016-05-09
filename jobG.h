#ifndef _JOBG_H_
#define _JOBG_H_

//Job Gomez
#include "ppm.h"
#include "game_objects.h"
#include <GL/glx.h>
#include "person.h"

unsigned char* buildAlphaData(Ppmimage *);
void job_opengl(Ppmimage *personImage, GLuint personTexture);
void job_keys(int, int &quit, Person person, int &people);


#endif

