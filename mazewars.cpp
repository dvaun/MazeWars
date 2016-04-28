#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
#include "log.h"
//#include "Weapon.h"
//#include "Power_up.h"
//#include "Player.h"
#include "joystick.hh"
#include "game.h"
#include "matthewG.h"
#include <unistd.h> //required for controller
#include "davidV.h"

extern "C" {
	#include "fonts.h"
}

using namespace std;

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];
typedef int Explosive;

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                      (c)[1]=(a)[1]-(b)[1]; \
                      (c)[2]=(a)[2]-(b)[2]
//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
#define PI 3.141592653589793
#define ALPHA 1

//X Windows variables
Display *dpy;
Window win;
GLXContext glc;

//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
			(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------

int xres=1250, yres=900;

/*struct Bullet {
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
	struct Bullet *prev;
	struct Bullet *next;
	Bullet() {
		prev = NULL;
		next = NULL;
	}
	void operator=(Bullet x){
	    pos[0] = x.pos[0];
	    pos[1] = x.pos[1];
	    vel[0] = x.vel[0];
	    vel[1] = x.vel[1];
	    color[0] = x.color[0];
	    color[1] = x.color[1];
	    color[2] = x.color[2];
	    time = x.time;
	}
};

const int MAX_BULLETS = 4;
 
struct Game {
	Player Player_1;
	Weapon gun;
	Bullet *barr;
	int nbullets;
    int score = 0;
	struct timespec bulletTimer;
	Game() {
		barr = new Bullet[MAX_BULLETS];
		nbullets = 0;
	}
};
*/
int keys[65536];
int joy[65536];
int axis[65536];
//function prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e, Game *game);
void pointPlayer(Game *g, int savex, int savey);
void check_controller(JoystickEvent event);
int check_keys(XEvent *e);
void init(Game *g);
void init_sounds(void);
void physics(Game *game);
void render(Game *game);

int main(void)
{
	logOpen();
	initXWindows();
	init_opengl();
	Game game;
	Joystick joystick;
	init(&game);
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
	int done=0;
	while (!done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_resize(&e);
			check_mouse(&e, &game);
			done = check_keys(&e);
		}

		//Joystick events need to be checked outside of XPending(dpy)
		JoystickEvent event;
		if (joystick.sample(&event)) {
			if (event.isButton() || event.isAxis()){
			//	std::cout << "entered at least" << std::endl;
				check_controller(event);
			}
		}
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		while (physicsCountdown >= physicsRate) {
			physics(&game);
			physicsCountdown -= physicsRate;
		}
		render(&game);
		glXSwapBuffers(dpy, win);
	}
	cleanupXWindows();
	cleanup_fonts();
	logClose();
	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void set_title(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "Maze Wars");
}

void setup_screen_res(const int w, const int h)
{
	xres = w;
	yres = h;
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;
	setup_screen_res(xres, yres);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		std::cout << "\n\tcannot connect to X server" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		std::cout << "\n\tno appropriate visual found\n" << std::endl;
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
			vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}

void reshape_window(int width, int height)
{
	//window has been resized.
	setup_screen_res(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, xres, 0, yres, -1, 1);
	set_title();
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, xres, yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, xres, 0, yres, -1, 1);
	//
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_FOG);
	glDisable(GL_CULL_FACE);
	//
	//Clear the screen to black
	glClearColor(0.0, 0.0, 0.0, 1.0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
}

void check_resize(XEvent *e)
{
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != xres || xce.height != yres) {
		//Window size did change.
		reshape_window(xce.width, xce.height);
	}
}

void init(Game *g) {
	clock_gettime(CLOCK_REALTIME, &g->bulletTimer);
	memset(keys, 0, 65536);
}

void normalize(Vec v) {
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0f;
		v[1] = 0.0f;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}

void check_mouse(XEvent *e, Game *g)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
	//point player at mouse
	pointPlayer(g, savex, savey);
}
void pointPlayer(Game *g, int savex, int savey){
        //Make the player point at the cursor
	g->gun.pos[0] = g->Player_1.pos[0];
	g->gun.pos[1] = g->Player_1.pos[1];
        float weaponx = g->gun.pos[0];
        float weapony = g->gun.pos[1];

        float nDeg = atan(((yres-savey)-(weapony))/((savex)-(weaponx))) * 180 / PI;

        if(savex > weaponx && (yres - savey) > weapony){
            nDeg += 180;
        }
        if(savex > weaponx && (yres - savey) < weapony){
            nDeg -= 180;
        }
        if(g->gun.angle > 360.f)
            g->gun.angle = 360.0f;
        if (g->gun.angle <= 360.0f){
            if(nDeg > 270)
                nDeg -= 360;
            g->gun.angle = nDeg + 90;
        }
        if (g->gun.angle < 0.0f)
            g->gun.angle += 360.0f;
}

void check_controller(JoystickEvent event)
{
	int number = event.number;
	if (event.type == 0x01) {
		if (joy[number] == 0)
			joy[number] = 1;
		else
			joy[number] = 0;
	}

	if (event.type == 0x02) {
		float value = event.value;
		//std::cout << value << std::endl;
		if (fabs(value) / (float) event.MAX_AXES_VALUE < .2)
			axis[number] = 0;
		else
			axis[number] = value;
	}
}

int check_keys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
	//
	//This code maintains an array of key status values.
	if (e->type == KeyRelease) {
		keys[key]=0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	if (e->type == KeyPress) {
		keys[key]=1;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift=1;
			return 0;
		}
	} else {
		return 0;
	}
	if (shift){}
	switch(key) {
		case XK_Escape:
			return 1;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
	}
	return 0;
}

/*void movement(Game *g) {
	Flt rad = ((g->Player_1.angle+90.0f) / 360.0f) * PI * 2.0f;
	
	Flt xdir = cos(rad);
	Flt ydir = sin(rad);

	g->Player_1.vel[0] = xdir*2.0f;
	g->Player_1.vel[1] = ydir*2.0f;
} */
	

void physics(Game *g)
{
	//Update Player_1 position
	g->Player_1.pos[0] += g->Player_1.vel[0];
	g->Player_1.pos[1] += g->Player_1.vel[1];
	//Check for collision with window edges
	if (g->Player_1.pos[0] < 0.0f) {
		g->Player_1.pos[0] += (float)xres;
	}
	else if (g->Player_1.pos[0] > (float)xres) {
		g->Player_1.pos[0] -= (float)xres;
	}
	else if (g->Player_1.pos[1] < 0.0f) {
		g->Player_1.pos[1] += (float)yres;
	}
	else if (g->Player_1.pos[1] > (float)yres) {
		g->Player_1.pos[1] -= (float)yres;
	}
	//
	//
	//Update bullet positions
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	for (int i=0; i<g->nbullets; i++) {
		Bullet *b = &g->barr[i];
		//How long has bullet been alive?
		double ts = timeDiff(&b->time, &bt);
		if (ts > 0.5f) {
			//Delete bullet here.
			for(int k = i; k < g->nbullets-1; k++){
				g->barr[k] = g->barr[k+1];
			}
			g->nbullets--;
		}
		//move the bullet
		b->pos[0] += b->vel[0];
		b->pos[1] += b->vel[1];
		//Check for collision with window edges
		if (b->pos[0] < 0.0f) {
			b->pos[0] += (float)xres;
		}
		else if (b->pos[0] > (float)xres) {
			b->pos[0] -= (float)xres;
		}
		else if (b->pos[1] < 0.0f) {
			b->pos[1] += (float)yres;
		}
		else if (b->pos[1] > (float)yres) {
			b->pos[1] -= (float)yres;
		}
	}
	//---------------------------------------------------
	//check keys pressed now
	if (keys[XK_a]) {
		g->Player_1.angle += 4.0f;
		if (g->Player_1.angle >= 360.0f)
			g->Player_1.angle -= 360.0f;
	}
	if (keys[XK_d]) {
		g->Player_1.angle -= 4.0f;
		if (g->Player_1.angle < 0.0f)
			g->Player_1.angle += 360.0f;

	}
	if (keys[XK_w]) {
		//convert Player_1 angle to radians
		Flt rad = ((g->Player_1.angle+90.0f) / 360.0f) * PI * 2.0f;
		//convert angle to a vector
		Flt xdir = cos(rad);
		Flt ydir = sin(rad);
		g->Player_1.vel[0] = xdir;
		g->Player_1.vel[1] = ydir;
	}else{
        g->Player_1.vel[0] = 0;
        g->Player_1.vel[1] = 0;
    }

	checkController(axis, g);

	/*//Check Controller 

	//calculated myself instead of using Vec + normalize
	//Vec + normalize didn't work as intended
	float x = axis[0]/32767.0;	
	float y = -axis[1]/32767.0;
	
	//	std::cout << "x: " << x << std::endl;
	//	std::cout << "y: " << y << std::endl;
	float twoPos = sqrt(2 + sqrt(2))/2.0; //.9238
	float twoNeg = sqrt(2 - sqrt(2))/2.0; //.3827
	//std::cout << "twoPos: " << twoPos << std::endl;
	//std::cout << "twoNeg: " << twoNeg << std::endl;

	//Up and Left
	if (x >= -twoPos+.08 && x <= -twoNeg+.08 && 
		y >= twoNeg-.08 && y <= twoPos+.08) {
		g->Player_1.angle = 45.0f;
		movement(g);
	}
	//Up and Right
	else if (x >= twoNeg+.08 && x <= twoPos+.08 && 
			y <= twoPos+.08 && y >= twoNeg-.08) { 
		g->Player_1.angle = -45.0f;
		movement(g);
	}
	//Left and Down	
	else if (x >= -twoPos+.08 && x <= -twoNeg-.08 && 
			y <= -twoNeg-.08 && y >= -twoPos+.08) {
		g->Player_1.angle = 135.0f;
		movement(g);
	}
	//Down and Right
	else if (x >= twoNeg-.08 && x <= twoPos+.08 && 
			y >= -twoPos+.08 && y <= -twoNeg-.08) {
		g->Player_1.angle = 225.0f;
		movement(g);
	}
	//Up
	else if (x <= twoNeg+.08 && x >= -twoNeg-.08 && y >= twoPos-.08 ) {  
		g->Player_1.angle = 0.0f;
		movement(g);
	}

	//Left
	else if (x <= -twoPos+.08 && y <= twoNeg+.08 && y >= -twoNeg+.08) {
		g->Player_1.angle = 90.0f;
		movement(g);
	}

	//Down
	else if(fabs(x) <= twoNeg+.08 && -fabs(y) <= -twoPos+.08) {
		g->Player_1.angle = 180.0f;
		movement(g);
	}

	//Right
	else if ( x >= twoPos-.08 && y <= twoNeg+.08 && y >= -twoNeg+.08) {
			g->Player_1.angle = 270.0f;
			movement(g);
	}
	else {
        g->Player_1.vel[0] = 0;
        g->Player_1.vel[1] = 0;
    }
	*/

    if (keys[XK_s]) {
        //convert Player_1 angle to radians
        Flt rad = ((g->Player_1.angle+90.0f) / 360.0f) * PI * 2.0f;
        //convert angle to a vector
        Flt xdir = cos(rad);
        Flt ydir = sin(rad);
        g->Player_1.vel[0] = -1 * xdir;
        g->Player_1.vel[1] = -1 * ydir;
    }
	if (keys[XK_space] || joy[0]) {
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g->bulletTimer, &bt);
		if (ts > 0.1 && g->nbullets < MAX_BULLETS) {
			timeCopy(&g->bulletTimer, &bt);
			//shoot a bullet...
			Bullet *b = &g->barr[g->nbullets];
			timeCopy(&b->time, &bt);
			b->pos[0] = g->gun.pos[0];
			b->pos[1] = g->gun.pos[1];
			b->vel[0] = g->gun.vel[0];
			b->vel[1] = g->gun.vel[1];
			//convert Player_1 angle to radians
			Flt rad = ((g->gun.angle+90.0f) / 360.0f) * PI * 2.0f;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			b->pos[0] += xdir*20.0f;
			b->pos[1] += ydir*20.0f;
			b->vel[0] += xdir*6.0f + rnd()*0.1f;
			b->vel[1] += ydir*6.0f + rnd()*0.1f;
			b->color[0] = 1.0f;
			b->color[1] = 1.0f;
			b->color[2] = 1.0f;
			g->nbullets++;
		}
	}
}

void render(Game *g)
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Draw the Player_1
	drawPlayer(g->Player_1);
	
	//Draw the bullets
	for (int i=0; i<g->nbullets; i++) {
		Bullet *b = &g->barr[i];
		drawBullet(b, 1.0, 1.0, 1.0);
	}
}

