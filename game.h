#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include "Player.h"
#include "defs.h"

const int MAX_BULLETS = 4;


struct Stats {
	double width, height;
	double radius;
	double speed;
	Vec gpos;
	Vec color;
	const char* image;
	Stats() {
		width = 0;
		height = 0;
		radius = 0;
		speed = 0;
		gpos[0] = 0;
		gpos[1] = 0;
		gpos[2] = 0;
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
	}
	void setImage(char* fname) {
		image = fname;
	}
	~Stats() {}
};

struct Object {
	Stats stats;
	Object() {}
	~Object() {}
};

struct Particle {
	Stats stats;
	int drawn;
	Vec vel;
	Vec pos;
	Particle() {
	    drawn = 0;
	    //stats = (Stats) malloc(sizeof(Stats));
	}
	~Particle() {}
};

typedef struct game_block_def {
    double width, height;
    int rows, columns;
} gblock_info;

typedef struct game_block_type {
    Stats stats;
    int type, assigned;
    game_block_type() {
	type = 0;
	assigned = 0;
    }
    void operator=(game_block_type gb) {
	stats.gpos[0] = gb.stats.gpos[0];
	stats.color[0] = gb.stats.color[0];
	stats.width = gb.stats.width;
	stats.height = gb.stats.height;
    }
} gblock;

typedef struct game_camera {
    int xprimary, yprimary;
    int xsecondary, ysecondary;
} gcamera;

#endif
