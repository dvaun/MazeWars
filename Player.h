struct Player {
	Vec dir;
	Vec pos;
	Vec vel;
	float angle;
	float color[3];
	PowerUp P_UP[3];
	int Max_Health;
	int Current_Health;
	Explosive P_Secondary;

	Player() {
		VecZero(dir);
		pos[0] = (Flt)(40);
		pos[1] = (Flt)(40);
		pos[2] = 0.0f;
		VecZero(vel);
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
