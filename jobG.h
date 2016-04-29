//Job Gomez
int xres = 1250;
int yres = 800;
int done = 0;
typedef float Flt;
typedef float Vec[3];
typedef Flt     Matrix[4][4];

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Ship {
        Vec dir;
        Vec pos;
        Vec vel;
        float angle;
        float color[3];
        Ship() {
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
}p;

int keys[65536];
p person;
Ppmimage *personImage = NULL;
GLuint personTexture;
int person = 0;

void init_opengl(void);
void check_keys(XEvent *e);
