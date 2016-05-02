#ifndef _PERSON_H_
#define _PERSON_H_

#include "defs.h"

struct Person {
		Vec dir;
        Vec pos;
		Vec lastpos;
        Vec vel;
        float angle;
        float color[3];
        Person() {
        	VecZero(dir);
            pos[0] = (Flt)(1250/2);
            pos[1] = (Flt)(900/2);
            pos[2] = 0.0f;
            VecZero(vel);
            angle = 0.0;
            color[0] = 1.0;
            color[1] = 1.0;
            color[2] = 1.0;
        }
};
#endif
