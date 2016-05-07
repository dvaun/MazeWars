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
// Templates section
//
//
template<typename T>
struct is_pointer { static const bool value = false; };

template<typename T>
struct is_pointer<T*> { static const bool value = true; };

template <typename OType>
void drawOType(OType otype, Game *g)
{
	Stats stats;
	stats = otype.stats;
	if (checkDistanceStats(otype, g, g->g_xres/2,g->g_yres/2)) {
		float xdist, ydist;
		setColor(stats);
		xdist = (stats.gpos[0] - g->Player_1.stats.gpos[0]);
		ydist = (stats.gpos[1] - g->Player_1.stats.gpos[1]);
		otype.draw(xdist, ydist);
	}
}

template <typename OType>
bool checkDistanceStats(OType otype, Game *g, float xcheck, float ycheck)
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

template <typename OType>
bool checkDistanceStats(OType *otype, Game *g, float xcheck, float ycheck)
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
//
//
//
#endif
