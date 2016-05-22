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
#include "roseP.h"
#include "jobG.h"
#include "davidV.h"
#include "defs.h"
#include "person.h"
#include "fonts/fonts.h"
#include "cameronM.h"
#include "cameronM.cpp"
#include </usr/include/AL/alut.h>
#include "mtime.h"

using namespace std;

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
//const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
struct timespec timeT1;
struct timespec timeT2;
struct timespec timeT3;
struct timespec timeT4;
struct timespec timeT5;
double physicsCountdown=0.0;
double timeSpan=0.0;
double timeSpanT1=0.0;
double timeSpanT2=0.0;
double timeSpanT3=0.0;
double timeSpanT4=0.0;
double timeSpanT5=0.0;
//unsigned int upause=0;
/*double timeDiff(struct timespec *start, struct timespec *end) 
{
	return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) 
{
	memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------
*/
int xres=1250, yres=900;
int keys[65536];
int joy[65536];
int axis[65536];
GLuint texture[10];
int people = 0;

int titleScreen = 1;

Ppmimage *personImage1 = NULL;
GLuint personTexture1;

Ppmimage *introImages[10] = {NULL};
GLuint introTextures[10];
// GLuint titleTexture; //introTexture[0]
// GLuint boulderTexture; //introTexture[1]
// GLuint logoTexture; //introTexture[2]
// GLuint enterTexture; //introTexture[3]
// GLuint optionsTexture; //introTexture[4]

Person person;
int enterPressed = 0;

//function prototypes
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e, Game *game);
void pointPlayer(Game *g, int savex, int savey);
//void getJoystickEvent(JoystickEvent event);
int check_keys(XEvent *e);
void init(Game *g);
void physics(Game *game);
void render(Game *game);

int main(void)
{
	logOpen();
	initXWindows();
	init_opengl();
	init_sounds();
	load_sounds();
	Game game;
	gblock_info gbi;
	gbi.width = 16;
	gbi.height = 16;
	gbi.rows = 50;
	gbi.columns = 50;
	begin_game(game, gbi);
	Joystick joystick;
	init(&game);
	printf("%f\n",game.Player_1.stats.color[0]);
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
				getJoystickEvent(event, joy, axis);
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
		if (titleScreen) {
			//glBindTexture(GL_TEXTURE_2D, titleTexture);
			if (keys[XK_Return]) {
				enterPressed = keys[XK_Return];
			}
			titleScreen = renderTitleScreen(introTextures, introImages, enterPressed);
		}
		else {
			glClearColor(0.8, 0.8, 0.8, 1.0);
			render(&game);
		}
		glXSwapBuffers(dpy, win);
	}
	cleanupXWindows();
	cleanup_fonts();
	logClose();
	release_sounds();
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
	getScreenRes(w , h);
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;
	setup_screen_res(xres, yres);
	resolution(xres, yres);
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
	resolution(width, height);

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
	glDisable(GL_BLEND);
	//
	//Clear the screen to black
	glClearColor(0.8, 0.8, 0.8, 1.0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	//glGenTextures(2, texture);
	initialize_fonts();
	
	//personImage1 = ppm6GetImage((char*)"images/red.ppm");
	//personImage2 = ppm6GetImage((char*)"images/sprite.ppm");
	//string characterSelected = "red";
	//personImage1 = characterSelection(characterSelected);
	//job_opengl(personImage1, personTexture1);
	//job_opengl(personImage2, personTexture2);

	string characterSelected = "red";
	personImage1 = characterSelection(characterSelected);

	introImages[0] = ppm6GetImage((char*)"images/titleBackground.ppm");
	introImages[1] = ppm6GetImage((char*)"images/boulder.ppm");
	introImages[2] = ppm6GetImage((char*)"images/logo.ppm");
	introImages[3] = ppm6GetImage((char*)"images/enterBold.ppm");
	introImages[4] = ppm6GetImage((char*)"images/optionsBold.ppm");
	introImages[5] = ppm6GetImage((char*)"images/Arrow.ppm");

	glGenTextures(1, &personTexture1);
	glGenTextures(1, &introTextures[0]); //titleTexture
	glGenTextures(1, &introTextures[1]); //boulderTexture
	glGenTextures(1, &introTextures[2]); //logoTexture
	glGenTextures(1, &introTextures[3]); //enterTexture
	glGenTextures(1, &introTextures[4]); //optionsTexture
	glGenTextures(1, &introTextures[5]); //ArrowTexture

	//Character Texture
	float w = personImage1->width;
	float h = personImage1->height;

	glBindTexture(GL_TEXTURE_2D, personTexture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *personData = buildAlphaData(personImage1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, personData);

	free(personData);

	//Title Screen Background Texture
	w = introImages[0]->width;
	h = introImages[0]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *titleBackgroundData = buildAlphaData(introImages[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, 
			GL_UNSIGNED_BYTE, titleBackgroundData);
	free(titleBackgroundData);

	//boulder falling texture
	w = introImages[1]->width;
	h = introImages[1]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *boulderData = buildAlphaData(introImages[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, boulderData);
	free(boulderData);

	//MazeWars logo texture
	w = introImages[2]->width;
	h = introImages[2]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *logoData = buildAlphaData(introImages[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, logoData);
	free(logoData);

	//enter maze texture
	w = introImages[3]->width;
	h = introImages[3]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *enterData = buildAlphaData(introImages[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, enterData);
	free(enterData);

	//options texture
	w = introImages[4]->width;
	h = introImages[4]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *optionsData = buildAlphaData(introImages[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, optionsData);
	free(optionsData);

	//Arrow Texture
	w = introImages[5]->width;
	h = introImages[5]->height;
	glBindTexture(GL_TEXTURE_2D, introTextures[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *arrowData = buildAlphaData(introImages[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, arrowData);
	free(arrowData);
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
		//reshape_window(xce.width, xce.height);
		XResizeWindow(dpy, win, xres, yres);
	}
}

void init(Game *g) 
{
	clock_gettime(CLOCK_REALTIME, &g->bulletTimer);
	memset(keys, 0, 65536);
	g->Player_1.stats.color[0] = 255;
	g->Player_1.stats.spos[0] = 625;
	g->Player_1.stats.spos[1] = 450;
	printf("%f\n",g->Player_1.stats.color[0]);
}

void normalize(Vec v) 
{
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

int check_keys(XEvent *e)
{
	//keyboard input?
	int quit;
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
	job_keys(key, quit, person, people);
	if (quit == 1) 
	return 1;
	else
	return 0;
}

void physics(Game *g)
{
	updateObjGposStat(&g->Player_1);
	updateObjGposStat(&g->gun);

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
		b->stats.gpos[0] += 6*b->stats.vel[0];
		b->stats.gpos[1] += 6*b->stats.vel[1];
	}
	if (keys[XK_a] && !g->Player_1.gameOver) {
		g->Player_1.stats.angle += 4.0f;
		if (g->Player_1.stats.angle >= 360.0f)
		g->Player_1.stats.angle -= 360.0f;

		person.pos[0] =	g->Player_1.stats.spos[0];
		person.pos[1] = g->Player_1.stats.spos[1];
	}
	if (keys[XK_d] && !g->Player_1.gameOver) {
		g->Player_1.stats.angle -= 4.0f;
		if (g->Player_1.stats.angle < 0.0f)
		g->Player_1.stats.angle += 360.0f;
	}
	if (keys[XK_w] && !g->Player_1.gameOver) {
		//convert Player_1.stats.angle to radians
		Flt rad = ((g->Player_1.stats.angle+90.0f) / 360.0f) * PI * 2.0f;
		//convert angle to a vector
		Flt xdir = cos(rad);
		Flt ydir = sin(rad);
		g->Player_1.stats.vel[0] = xdir;
		g->Player_1.stats.vel[1] = ydir;
		timeSpanT5 = timeDiff(&timeT5, &timeCurrent);
        if(timeSpanT5 > 0.3){
			clock_gettime(CLOCK_REALTIME, &timeT5);
			play_sounds(2);
		}
	} else {
		g->Player_1.stats.vel[0] = 0;
		g->Player_1.stats.vel[1] = 0;
	}
	if (keys[XK_s] && !g->Player_1.gameOver) {
		//convert Player_1.stats.angle to radians
		Flt rad = ((g->Player_1.stats.angle+90.0f) / 360.0f) * PI * 2.0f;
		//convert angle to a vector
		Flt xdir = cos(rad);
		Flt ydir = sin(rad);
		g->Player_1.stats.vel[0] = -1 * xdir;
		g->Player_1.stats.vel[1] = -1 * ydir;
		timeSpanT5 = timeDiff(&timeT5, &timeCurrent);
		if(timeSpanT5 > 0.3){
			clock_gettime(CLOCK_REALTIME, &timeT5);
			play_sounds(2);
		}
	}
	if (axis[0] || axis[1] ||  axis[4] || axis[5]) {	
		checkController(axis, g);
	}

	if ((keys[XK_space] || joy[0]) && g->Player_1.Current_Ammo > 0 && 
									  g->Player_1.Current_Health > 0) {
		g->Player_1.stats.angle = g->gun.stats.angle;
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g->bulletTimer, &bt);
		if (ts > 0.1 && g->nbullets < MAX_BULLETS) {
			 play_sounds(0);
			timeCopy(&g->bulletTimer, &bt);
			//shoot a bullet...
			Bullet *b = &g->barr[g->nbullets];
			timeCopy(&b->time, &bt);
			b->stats.gpos[0] = g->gun.stats.gpos[0];
			b->stats.gpos[1] = g->gun.stats.gpos[1];
			b->stats.vel[0] = g->gun.stats.vel[0];
			b->stats.vel[1] = g->gun.stats.vel[1];
			//convert Player_1.stats.angle to radians
			Flt rad = ((g->gun.stats.angle+90.0f) / 360.0f) * PI * 2.0f;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			b->stats.gpos[0] += xdir*20.0f;
			b->stats.gpos[1] += ydir*20.0f;
			b->stats.vel[0] += xdir*6.0f + rnd()*0.1f;
			b->stats.vel[1] += ydir*6.0f + rnd()*0.1f;
			b->stats.color[0] = 1.0f;
			b->stats.color[1] = 1.0f;
			b->stats.color[2] = 1.0f;
			g->nbullets++;
			g->Player_1.Current_Ammo--;
		}
	}
	if(keys[XK_F7] && !g->Player_1.gameOver){
		if(g->Player_1.Current_Health > 0)
		g->Player_1.Current_Health -= 5;
	}
	if(keys[XK_F6]){
		Restart(&g->Player_1);
	}
	if(keys[XK_F8]){
		timeSpanT1 = timeDiff(&timeT1, &timeCurrent);
		if(timeSpanT1 > 0.2){
			clock_gettime(CLOCK_REALTIME, &timeT1);
			g->Player_1.artifact[0] = !g->Player_1.artifact[0];
		}
	}
	if(keys[XK_F9]){
		timeSpanT2 = timeDiff(&timeT2, &timeCurrent);
                if(timeSpanT2 > 0.2){
                        clock_gettime(CLOCK_REALTIME, &timeT2);
                        g->Player_1.artifact[1] = !g->Player_1.artifact[1];
                }
	}
	if(keys[XK_F10]){
		timeSpanT3 = timeDiff(&timeT3, &timeCurrent);
                if(timeSpanT3 > 0.2){
                        clock_gettime(CLOCK_REALTIME, &timeT3);
                        g->Player_1.artifact[2] = !g->Player_1.artifact[2];
                }

	}
	if(keys[XK_F12]){
		timeSpanT4 = timeDiff(&timeT4, &timeCurrent);
                if(timeSpanT4 > 0.2){
                        clock_gettime(CLOCK_REALTIME, &timeT4);
		g->Player_1.lives += 1;
		g->Player_1.lives = g->Player_1.lives % 5;
	}
	}
}

//struct timespec animationStart, animationCurrent;
//double animationSpan=0.0;
static int a = 0;
void render(Game *g)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//if(animationSpan > 60/1000.0f) {	
	//	clock_gettime(CLOCK_REALTIME, &animationStart);
	//}
	drawGBlocks(g);
	//Draw the Player_1
	//if(g->Player_1.Current_Health > 0 && !g->Player_1.gameOver)
	//	drawOType(g->Player_1, g);
	
	if (axis[3] || axis[4])
		renderCrosshair(axis, g, false);
	if (joy[4] || keys[XK_b]) 
		renderShield(g);	
	shadowBox();
	drawHUD(g->Player_1);
	if(g->Player_1.Current_Health == 0){
		g->Player_1.lives--;
		//Play death groan upon player death
		if (g->Player_1.lives == 0)
			play_sounds(1);
		g->Player_1.Current_Health = g->Player_1.Max_Health;
	}
	if(g->Player_1.lives == 0){
		GameOver();
		g->Player_1.gameOver = true;
	}
	//drawHealthPack(500, 400, 0);
	//drawHealthPack(100, 800, 0);
	float w = personImage1->width/4;
 
	if (g->Player_1.gameOver == false)
		renderCharacter(person, g, w, keys, personTexture1); 

	for (int i=0; i<g->nbullets; i++) {
		Bullet *b = &g->barr[i];
		if (b != NULL)
			drawBullet(g, b, 0.0, 0.0, 0.0);	
	}
}
