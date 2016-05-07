#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Power_up.h"
#include "defs.h"
#include "game.h"

typedef int Explosive;


struct Player {
	Stats stats;
	Vec dir;
	Vec pos;
	float angle;
	PowerUp P_UP[3];
	int Max_Health;
	int Current_Health;
	int Current_Ammo = 100;
	int Max_Ammo = 100;
	Explosive P_Secondary;

	Player() {
		stats = new Stats;
		speed = 2.0;
		VecZero(dir);
		pos[0] = 625;
		pos[1] = 450;
		pos[2] = 0.0f;
		VecZero(vel);
		Current_Health = 100;
		Max_Health = 100;
		angle = 0.0;
		//PowerUp type=0 is the default no powerup option
		P_UP[0] = 0;
		P_UP[1] = 0;
		P_UP[2] = 0;
	}
};

#endif
