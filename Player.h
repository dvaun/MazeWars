#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Power_up.h"
#include "defs.h"

typedef int Explosive;


struct Player {
	Vec dir;
	Vec pos;
	Vec gpos;
	Vec vel;
	float speed;
	float angle;
	float color[3];
	PowerUp P_UP[3];
	int Max_Health;
	int Current_Health;
	int Current_Ammo = 100;
	int Max_Ammo = 100;
	Explosive P_Secondary;

	Player() {
		speed = 2.0;
		VecZero(dir);
		pos[0] = (Flt)(40);
		pos[1] = (Flt)(40);
		pos[2] = 0.0f;
		gpos[0] = 0;
		gpos[1] = 0;
		gpos[2] = 0;
		VecZero(vel);
		Current_Health = 100;
		Max_Health = 100;
		angle = 0.0;
		color[0] = 1.0;
		color[1] = 1.0;
		color[2] = 1.0;
		//PowerUp type=0 is the default no powerup option
		P_UP[0] = 0;
		P_UP[1] = 0;
		P_UP[2] = 0;
	}
};

#endif
