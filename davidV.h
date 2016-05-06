#ifndef DRAW_F
#define DRAW_F

#include "game_objects.h"
#include "game.h"
#include <cstring>

void setColor(Object);
void drawSquare(Object *, int, int, int);
void drawParticle(Particle *, int, int, int);
void drawBullet(Bullet *b, float red, float blue, float green);
void drawTextString(float, float, float, float, std::string);
void drawText(float, float, float, float);
void drawPlayer(Player p);
void assign_gblock(gblock &, Object &, int, int, int);
gblock return_gblock(gblock, int, int, int);
Game init_game(Game, gblock_info);
bool inDrawingDistanceBlock(Game *, gblock);
bool checkDistanceBlock(Game *, gblock, float, float);
void drawBlock(Game *, gblock);
void drawGBlocks(Game *);

void set_gblock_size(double&, double&, double);
void set_gblock_gpos(double&, int, int);
void create_gblock(gblock&, int, int, int);
void begin_game(Game&, gblock_info&);

void drawGameObject(Game *, Object);
void drawObject(Game *, Object);
bool checkDistanceObject(Game *, Object, float, float);
float getDistanceObjectVal(Game *, Object, int);
float getDistanceObject(Game *, Object);
float getXYDistValue(float, float);
#endif
