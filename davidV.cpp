// Lab 5
// David Vaughan
// 04/28/2016
//
// My code involves simplifying the render process by introducing draw
// functions. Current


#ifndef DRAW_F
#define DRAW_F

#include <GL/glx.h>
#include "game_objects.h"
#include "fonts/fonts.h"
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
void setColor(Object object)
{
	glColor3f((float) object.color[0],(float) object.color[1],(float) \
		object.color[2]);
}


/*
void drawSquare(Object *obj, int red, int blue, int green)
{
	setColor(*obj);
	glPushMatrix();
	glTranslatef(obj->pos[0], obj->pos[1], obj->pos[2]);
	glBegin(GL_QUADS);
		glVertex2i(-obj->width, -obj->height);
		glVertex2i(-obj->width, obj->height);
		glVertex2i(obj->width, obj->height);
		glVertex2i(obj->width, -obj->height);
	glEnd();
	glPopMatrix();
}
*/


void drawTextString(float x, float y, 
		float offsetx, float offsety, std::string printvalue)
{
	Rect r;
	std::string s;
	char const *c;
	r.center = 0;
	r.bot = x + offsety;
	r.left = y + offsetx;
	s = printvalue;
	c = s.c_str();
	ggprint8b(&r, 0, 0, "%s", c);
}

void drawText(float x, float y, float offsetx, float offsety, float printvalue)
{
	Rect r;
	std::string s;
	char const *c;
	r.center = 0;
	r.bot = x + offsety;
	r.left = y + offsetx;
	s = std::to_string(printvalue);
	c = s.c_str();
	ggprint8b(&r, 0, 0, "%s", c);
}


/*
void drawParticle(Particle *p, int red, int blue, int green)
{
	setColor(*p->obj);
	glPushMatrix();
	glTranslatef(p->obj->pos[0], p->obj->pos[1], p->obj->pos[2]);
	glBegin(GL_QUADS);
		glVertex2i(-p->obj->width, -p->obj->height);
		glVertex2i(-p->obj->width, p->obj->height);
		glVertex2i(p->obj->width, p->obj->height);
		glVertex2i(p->obj->width, -p->obj->height);
	glEnd();
	glPopMatrix();
}
*/


void drawBullet(Bullet *b, float red, float blue, float green)
{
	Object *bullet = b->obj;
	setColor(*bullet);
	glBegin(GL_POINTS);
	glVertex2f(bullet->gpos[0], bullet->gpos[1]);
	glVertex2f(bullet->gpos[0]-1.0f, bullet->gpos[1]);
	glVertex2f(bullet->gpos[0]+1.0f, bullet->gpos[1]);
	glVertex2f(bullet->gpos[0], bullet->gpos[1]-1.0f);
	glVertex2f(bullet->gpos[0], bullet->gpos[1]+1.0f);
	glColor3f(red - 0.2f, blue - 0.2f, green - 0.2f);
	glVertex2f(bullet->gpos[0]-1.0f, bullet->gpos[1]-1.0f);
	glVertex2f(bullet->gpos[0]-1.0f, bullet->gpos[1]+1.0f);
	glVertex2f(bullet->gpos[0]+1.0f, bullet->gpos[1]-1.0f);
	glVertex2f(bullet->gpos[0]+1.0f, bullet->gpos[1]+1.0f);
	glEnd();
}

// Cameron wrote some player render code w/Gordons
// ship as the temporary player - I've 
// basically put it into it's own draw function
// and added some features, ie the x/y pos text


void drawPlayer(Player p)
{
	glColor3fv(p.color);
	glPushMatrix();
	glTranslatef(625, 450, p.gpos[2]);
	glRotatef(p.angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(-12.0f, -10.0f);
		glVertex2f(  0.0f,  20.0f);
		glVertex2f(  0.0f,  -6.0f);
		glVertex2f(  0.0f,  -6.0f);
		glVertex2f(  0.0f,  20.0f);
		glVertex2f( 12.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
	glEnd();
	glPopMatrix();
	drawText(p.pos[0],p.pos[1],10,10,p.gpos[0]);
	drawText(p.pos[0],p.pos[1],10,-10,p.gpos[1]);
}

void assign_gblock(gblock &block, Object &object, int type, int row, int col)
{
	block.type = type;
	block.assigned = 1;
	object.gpos[0] = row * 50.0;
	object.gpos[1] = col * 50.0;
	printf("Block[%d][%d] located at x(%f) y(%f)\n",row,col,block.obj.gpos[0],block.obj.gpos[1]);
}

gblock return_gblock(gblock block, int type, int row, int col)
{
	block.type = type;
	block.assigned = 1;
	block.obj.gpos[0] = row * 50.0;
	block.obj.gpos[1] = col * 50.0;
	printf("Block[%d][%d] located at x(%f) y(%f)\n",row,col,block.obj.gpos[0],block.obj.gpos[1]);
	return block;
}

Game init_game(Game g, gblock_info gbi)
{
	Game game = g;

	game.game_info.rows = gbi.rows;
	game.game_info.columns = gbi.columns;
	game.blocks = new gblock*[gbi.rows];
	for (int i = 0; i < gbi.rows; i++) {
		game.blocks[i] = new gblock[gbi.columns];
	}
	/*
	assign_gblock(game.blocks[5][25],game.blocks[5][25].obj,1,5,25);
	assign_gblock(game.blocks[15][15],game.blocks[15][15].obj,1,15,15);
	assign_gblock(game.blocks[30][30],game.blocks[30][30].obj,1,30,30);
	assign_gblock(game.blocks[0][0],game.blocks[0][0].obj,0,0,10);
	assign_gblock(game.blocks[25][5],game.blocks[25][5].obj,0,25,5);
	assign_gblock(game.blocks[7][21],game.blocks[7][21].obj,0,7,21);
	*/
	game.blocks[5][5] = return_gblock(game.blocks[5][5],1,5,5);
	return game;
}

void set_gblock_gpos(double& gposition, int num, int bsize)
{
	gposition = (double)num * bsize;
}

void set_gblock_size(gblock& block, double& height, double& width, double size)
{
	block.obj.height = size;
	block.obj.width = size;
	height = size;
	width = size;
}

void create_gblock(gblock& block, int type, int row, int col)
{
	block.type = type;
	block.assigned = 1;
	set_gblock_gpos(block.obj.gpos[0],row,block.obj.width*2);
	set_gblock_gpos(block.obj.gpos[1],col,block.obj.width*2);
	printf("Block[%d][%d] located at x(%f) y(%f)\n",row,col,block.obj.gpos[0],block.obj.gpos[1]);
}

void begin_game(Game& game, gblock_info& gbi)
{
	game.game_info.rows = gbi.rows;
	game.game_info.columns = gbi.columns;
	game.blocks = new gblock*[gbi.rows];
	for (int i = 0; i < gbi.rows; i++) {
		game.blocks[i] = new gblock[gbi.columns];
	}
	for (int i = 0; i < gbi.rows; i++) {
	    for (int j = 0; j < gbi.columns; j++) {
		set_gblock_size(game.blocks[i][j],
			game.blocks[i][j].obj.height,
			game.blocks[i][j].obj.width, gbi.width);
	    }
	}
	create_gblock(game.blocks[5][5],1,5,5);
	create_gblock(game.blocks[15][5],0,15,5);
	create_gblock(game.blocks[10][5],1,10,5);
	for (int i = 0; i < 20; i++) {
	    create_gblock(game.blocks[20][i],1,20,i);
	    create_gblock(game.blocks[21][i],0,21,i);
	    create_gblock(game.blocks[22][i],1,22,i);
	}
}

//
//
// Rendering function section
//
//
//

bool inDrawingDistanceBlock(Game *g, gblock block)
{
	Player player = g->Player_1;
	bool indistancex = false, indistancey = false;
	printf("%f ",block.obj.gpos[0] - player.gpos[0] - 25);
	printf("%f\n",block.obj.gpos[1] - player.gpos[1] - 25);
	if (abs(player.gpos[0] - block.obj.gpos[0] - block.obj.width*2) < 625) {
		indistancex = true;
	}
	if (abs(player.gpos[1] - block.obj.gpos[1] - block.obj.width*2) < 450) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
}

/*
bool withinDistance(Player p, gblock block, int check)
{
	return (abs(p.gpos[0]
}
*/
float getXYDistValue(float x, float y) {
	return sqrt((x*x)+(y*y));
}
float getDistanceObjectVal(Game *g, Object obj, int coord)
{
	Player player = g->Player_1;
	float distance = player.gpos[coord] - obj.gpos[coord] 
			+ obj.width; 
	return distance;
}
float getDistanceObject(Game *g, Object obj)
{
	Player player = g->Player_1;
	float distancex = player.gpos[0] - obj.gpos[0] 
			+ obj.width;
	float distancey = player.gpos[1] - obj.gpos[1] 
			+ obj.width;
	float distance = sqrt((distancex*distancex)+(distancey*distancey));
	return distance;
}

bool checkDistanceBlock(Game *g, gblock block, float xcheck, float ycheck)
{
	Player player = g->Player_1;
	bool indistancex = false, indistancey = false;
	if (abs(player.gpos[0] - block.obj.gpos[0] + block.obj.width) < xcheck) {
		indistancex = true;
	}
	if (abs(player.gpos[1] - block.obj.gpos[1] + block.obj.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}

bool checkDistanceObject(Game *g, Object obj, float xcheck, float ycheck)
{
	Player player = g->Player_1;
	bool indistancex = false, indistancey = false;
	if (abs(player.gpos[0] - obj.gpos[0] + obj.width) < xcheck) {
		indistancex = true;
	}
	if (abs(player.gpos[1] - obj.gpos[1] + obj.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}

/*
void getDistanceBlock(Game *g, gblock block, int xcheck, int ycheck)
{
	Vec distance;
	Player player = g->Player_1;
	bool indistancex = false, indistancey = false;
	if (abs(player.gpos[0] - block.obj.gpos[0] - 50) < xcheck) {
		indistancex = true;
	}
	if (abs(player.gpos[1] - block.obj.gpos[1] - 50) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
	    return Vec;
	}
	return -1;
}
*/
void drawObject(Game *g, Object obj)
{
	Player player = g->Player_1;
	float xdist, ydist;
	xdist = 625 + (obj.gpos[0] - g->Player_1.gpos[0] - obj.width);
	ydist = 450 + (obj.gpos[1] - g->Player_1.gpos[1] - obj.width);
	float size = obj.width;
	glColor3f((int)obj.color[0], (int)obj.color[1], (int)obj.color[2]);
	glPushMatrix();
	glTranslatef(xdist, ydist, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-size, -size);
		glVertex2f(-size, size);
		glVertex2f(size, size);
		glVertex2f(size, -size);
	glEnd();
	glPopMatrix();
	drawTextString(ydist,xdist,-25,0,"davidbox");	
}

void drawBlock(Game *g, gblock block)
{
	Player player = g->Player_1;
	float xdist, ydist;
	xdist = 625 + (block.obj.gpos[0] - player.gpos[0] - block.obj.width);
	ydist = 450 + (block.obj.gpos[1] - player.gpos[1] - block.obj.width);
	float size = block.obj.width;
	glPushMatrix();
	glTranslatef(xdist, ydist, 0.0f);
	glBegin(GL_QUADS);
		glVertex2f(-size, -size);
		glVertex2f(-size, size);
		glVertex2f(size, size);
		glVertex2f(size, -size);
	glEnd();
	glPopMatrix();
	drawText(block.obj.gpos[0],block.obj.gpos[1],10,10,block.obj.gpos[0]);
	drawText(block.obj.gpos[0],block.obj.gpos[1],10,-10,block.obj.gpos[1]);
}

void drawGameObject(Game *g, Object object)
{
	if (checkDistanceObject(g, object, g->g_xres/2, g->g_yres/2)) {
		drawObject(g, object);
	}
}

void drawGBlocks(Game *g)
{
	int nrows = g->game_info.rows;
	int ncols = g->game_info.columns;
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (g->blocks[i][j].assigned == 1) {
				if (checkDistanceBlock(g,g->blocks[i][j],(float)g->g_xres/2,(float)g->g_yres/2)) {
					if (g->blocks[i][j].type == 1) {
						glColor3f(1.0,0.0,0.0);
					} else {
						glColor3f(0.0,1.0,0.0);
					}
					drawBlock(g, g->blocks[i][j]);
				}
			}
		}
	}
}

void check_gblock_collision(Game *g)
{
	int nrows = g->game_info.rows;
	int ncols = g->game_info.columns;
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (g->blocks[i][j].assigned == 1) {
				if (checkDistanceBlock(g,g->blocks[i][j],50,50)) {
					
				}
			}
		}
	}
}

//
//
//
//
#endif
