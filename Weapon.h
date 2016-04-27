typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];
typedef int Explosive;
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
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
