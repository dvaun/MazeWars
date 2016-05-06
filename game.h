#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include "Player.h"
#include "defs.h"

const int MAX_BULLETS = 4;


struct Object {
	double width, height;
	double radius;
	double speed;
	Vec center;
	Vec gpos;
	Vec color;
};

struct Particle {
	Object *obj;
	int drawn;
	Vec vel;
	Vec pos;
	Particle() {
	    drawn = 0;
	    obj = (Object*) malloc(sizeof(Object));
	}
};

typedef struct game_block_def {
    double width, height;
    int rows, columns;
} gblock_info;

typedef struct game_block_type {
    Object obj;
    int type, assigned;
    game_block_type() {
	type = 0;
	assigned = 0;
    }
    void operator=(game_block_type gb) {
	obj.gpos[0] = gb.obj.gpos[0];
	obj.color[0] = gb.obj.color[0];
	obj.width = gb.obj.width;
	obj.height = gb.obj.height;
    }
} gblock;

typedef struct game_camera {
    int xprimary, yprimary;
    int xsecondary, ysecondary;
} gcamera;

#endif
