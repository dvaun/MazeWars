#ifndef DRAW_F
#define DRAW_F

#include "game_objects.h"
#include "game.h"
#include <cstring>

template <typename OType>
void drawOType(OType otype, Game *g);
template <typename OType>
bool checkDistanceStats(OType otype, Game *g, float xcheck, float ycheck);

void setColor(Stats);
void drawSquare(Stats *, int, int, int);
void drawParticle(Particle *, int, int, int);
void drawBullet(Game *g, Bullet *b, float red, float blue, float green);
void drawTextString(float, float, float, float, std::string);
void drawText(float, float, float, float);
void drawPlayer(Player p);
void assign_gblock(gblock &, Stats &, int, int, int);
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

void drawGameStats(Game *, Stats);
void drawStats(Game *, Stats);
bool checkDistanceStats(Game *, Stats, float, float);
float getDistanceStatsVal(Game *, Stats, int);
float getDistanceStats(Game *, Stats);
float getXYDistValue(float, float);
//
//
void init_blocks(Game *, gblock_info);
//***************************************
//***************************************
//
// Templates section
//
//***************************************
//***************************************
template <class T>
class Class
{
	public:
	Class(const Class &){}
	Class & operator=(const Class& c){return *this;}
};

template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

// Checks the distance for objects via their stats
// will be used in draw function and likely physics
template <typename OType>
bool checkPlayerDistanceOType(OType otype, Game *g, float xcheck, float ycheck)
{
	Player player = g->Player_1;
	Stats stats;
	stats = otype.stats;
	bool indistancex = false, indistancey = false;
	if (abs(player.stats.gpos[0] - stats.gpos[0] +
		    		stats.width) < xcheck) {
		indistancex = true;
	}
	if (abs(player.stats.gpos[1] - stats.gpos[1] +
		    		stats.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}

// Another specialization, once again for stats
// and if the objects are pointers
template <typename OType>
bool checkPlayerDistanceOType(OType *otype, Game *g, float xcheck, float ycheck)
{
	Player player = g->Player_1;
	Stats stats;
	stats = otype->stats;
	bool indistancex = false, indistancey = false;
	if (abs(player.stats.gpos[0] - stats.gpos[0] +
		    		stats.width) < xcheck) {
		indistancex = true;
	}
	if (abs(player.stats.gpos[1] - stats.gpos[1] +
		    		stats.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}
template <typename OType>
bool checkBlockDistanceOType(OType otype, gblock block, float xcheck, float ycheck)
{
	Stats stats = otype.stats;
	bool indistancex = false, indistancey = false;
	if (abs(stats.gpos[0] - block.stats.gpos[0] +
		    		block.stats.width) < xcheck) {
		indistancex = true;
	}
	if (abs(stats.gpos[1] - block.stats.gpos[1] +
		    		block.stats.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}

// Another specialization, once again for stats
// and if the objects are pointers
template <typename OType>
bool checkBlockDistanceOType(OType *otype, gblock block, float xcheck, float ycheck)
{
	Stats stats = otype->stats;
	bool indistancex = false, indistancey = false;
	if (abs(otype->stats.gpos[0] - block.stats.gpos[0] +
		    		block.stats.width) < xcheck) {
		indistancex = true;
	}
	if (abs(otype->stats.gpos[1] - block.stats.gpos[1] +
		    		block.stats.width) < ycheck) {
		indistancey = true;
	}
	if (indistancex && indistancey) {
		return true;
	}
	return false;
}
// Template for objects with stats class - should apply to basically everything
template <typename OType>
void drawOType(OType otype, Game *g)
{
	Player p = g->Player_1;
	Stats stats;
	stats = otype.stats;
	if (checkDistanceStats(otype, g, g->g_xres/2,g->g_yres/2)) {
		float xdist, ydist;
		glColor3f(stats.color[0],stats.color[1],stats.color[2]);
		xdist = p.pos[0] + (stats.gpos[0] - p.stats.gpos[0] - stats.width);
		ydist = p.pos[1] + (stats.gpos[1] - p.stats.gpos[1] - stats.height);
		otype.draw(xdist, ydist, p.angle, p.pos);
	}
}

// Specialization for pointer objects
template <typename OType>
void drawOType(OType *otype, Game *g)
{
	Player p = g->Player_1;
	Stats stats;
	stats = otype->stats;
	if (checkDistanceStats(otype, g, g->g_xres/2,g->g_yres/2)) {
		float xdist, ydist;
		glColor3f(stats.color[0],stats.color[1],stats.color[2]);
		xdist = p.pos[0] + (stats.gpos[0] - p.stats.gpos[0] - stats.width);
		ydist = p.pos[1] + (stats.gpos[1] - p.stats.gpos[1] - stats.height);
		otype->draw(xdist, ydist, p.angle, p.pos);
	}
}


//*****************************
//*****************************
//
// Physics/collision templates
//
//*****************************
//*****************************
template <typename OType>
void check_gblock_collision(OType otype, Game *g, float xcheck, float ycheck)
{
	int nrows = g->game_info.rows;
	int ncols = g->game_info.columns;
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (g->blocks[i][j].assigned == 1) {
				if (checkBlockDistanceOType(otype,g->blocks[i][j],xcheck,ycheck)) {
					
				}
			}
		}
	}
}

//
//
//
#endif
