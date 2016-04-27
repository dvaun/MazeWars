struct Weapon{
    Vec dir;
    Vec pos;
    Vec vel;
    float angle;
    Weapon(){
	VecZero(dir);
        pos[0] = (Flt)(40);
        pos[1] = (Flt)(40);
        pos[2] = 0.0f;
        VecZero(vel);
        angle = 0.0;
    }
};
