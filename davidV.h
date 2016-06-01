#ifndef DRAW_F
#define DRAW_F

#include "game_objects.h"
#include "game.h"
#include "jobG.h"
#include <cstring>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <cmath>

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

char* getBlockTexture(gblock block);
void renderBlockTexture(gblock block);
//
//
void init_blocks(Game *, gblock_info);

/* block.h */

/*
 * Author: David Vaughan
 * Purpose: 2D Array generator
 * Code: This is the header file for the "BlockConstructor" code.
 * See block.cpp for more information
 */
// Macros and templates //
//
//
template <typename T>
bool checkVoid(T *t) {
	if (t == NULL) {
		return true;
	} else {
		return false;
	}
}
//
//
// End Macros and Templates //

struct DRules {
	int num_turns;
	int num_halls;
	int MIN_HALL_VER_LENGTH;
	int MAX_HALL_VER_LENGTH;
	int MIN_HALL_HOR_LENGTH;
	int MAX_HALL_HOR_LENGTH;
	int MAXDIST;
	int MINDIST;
};

struct DSpecs {
	int BLOCK_LENGTH;
	int game_time_considered;
	int rows;
	int cols;
	int player_speed;
};

struct DInit {
	int startrow;
	int startcol;
	int endrow;
	int endcol;
};

struct DCounter {
	int counter;
	int finalcount;
};

class BlockConstructor {
	public:
	int tread;
	int direction;
	int col;
	int row;
	BlockConstructor();
	void operator=(BlockConstructor);
	void operator=(BlockConstructor*);
	~BlockConstructor();
};

class Block {
public:
	int maintype;
	int subtype;
	int path;
	BlockConstructor blockc;
	Block *north;
	Block *east;
	Block *south;
	Block *west;
	Block *northeast;
	Block *northwest;
	Block *southeast;
	Block *southwest;
	Block();
	void operator=(Block);
	void operator=(Block*);
	~Block();
};

struct DFork {
	int forkpos[2];
	DFork *prev;
	DFork *next;
	DRules rules;
	int attempted_turns[4];
	void init();
};

class DForkMonitor {
public:
	DRules forkRules;
	DForkMonitor();
	~DForkMonitor();
	// linked-fork functions
	DFork* getNextFork(DFork *fork) {
		if (!checkVoid(fork)) return fork->next;
	}
	DFork* getPrevFork(DFork *fork) {
		if (!checkVoid(fork)) return fork->prev;
	}
	bool linkForks(DFork *fork_src, DFork *fork_trg) {
		if (!checkVoid(fork_src)) {
			fork_src->next = fork_trg;
			fork_trg->prev = fork_src;
			return true;
		} else {
		    return false;
		}
	}
	void traceForward(DFork *fork) {
		if (!checkVoid(fork)) {
			DFork *nextfork = fork->next;
			fork = nextfork;
		}
	}
	void traceBackward(DFork *fork) {
		if (!checkVoid(fork)) {
			DFork *prevfork = fork->prev;
			fork = prevfork;
		}
	}
};

/* end block.h */
/* array_functions.h */
using namespace std;

void generateRules(DRules& rules, DSpecs& specs, DInit& init);
void srandByTime(struct timespec& rtime);
void initGamePositions(DInit& init, DSpecs& specs, struct timespec rtime);
void initialize_values(DSpecs specs, DInit init, vector<vector<Block> > &);

/* end array_functions.h*/

/* events.h */

//#include "pathing_functions.h"
//#include "block.h"
//#include "array_functions.h"

bool mayHitWall(int, int, int, DSpecs, DRules);
int calc_hall_length(DSpecs, int, Block &, int, int);
Block DbuildHall(DRules, DSpecs, int, int, int, vector<vector<Block> > &,
				DCounter &);

/* end events.h */
/* pathing_functions.h */

//#include "block.h"

void pathingInit(DRules, DInit, DSpecs, vector<vector<Block> >&);
void buildPath(DRules, DInit, DSpecs, vector<vector<Block> >&);
void initStartBlocks(DRules, DInit, DSpecs, 
                vector<vector<Block> >&, struct timespec rtime);
int DnewDirection(DSpecs specs, DRules rules, Block&);
int DrandomDirection(int);
int DrandomDirection();
void initPath(DRules, DInit, DSpecs, vector<vector<Block> > &);
Block returnBuildBlock(int, int&, int&, vector<vector<Block> > &, int);
//Block returnBuildBlock(int, Block&, vector<vector<Block> > &, int);
//void buildBlock(int, Block&, vector<vector<Block> > &, int);
DFork getNewFork(Block);
void setDisabledTurn(DFork &, Block);
void setDisabledTurn(DFork &, Block, int);
bool checkAttemptedTurn(DFork, int);
void connectForks(DFork &, DFork &);

int parseSurroundingBlocks(DSpecs specs, vector<vector<Block> > &dungeon,
		Block block);
vector<vector<Block> > newParsedMap(DSpecs specs, int,
									vector<vector<Block> > &dungeon);

/* end pathing_functions.h */
//***************************************
//***************************************
//
// Templates section
//
//***************************************
//***************************************
//***************************************
//***************************************
//
// Operator= section, exchanging stats
// -- Many of these templates may just be
// copy-pasted to adjust for pointer obj
// -ects, only because I haven't figured
// out how to detect for pointer type
// inside the template functions.
//
//***************************************
//***************************************
template <typename Receiver, typename Source>
void exchangeGpos(Receiver receiver, Source source)
{
	receiver.stats.gpos[0] = source.stats.gpos[0];
	receiver.stats.gpos[1] = source.stats.gpos[1];
	receiver.stats.gpos[2] = source.stats.gpos[2];
}
template <typename Receiver, typename Source>
void exchangeGpos(Receiver *receiver, Source source)
{
	receiver->stats.gpos[0] = source.stats.gpos[0];
	receiver->stats.gpos[1] = source.stats.gpos[1];
	receiver->stats.gpos[2] = source.stats.gpos[2];
}
template <typename Receiver, typename Source>
void exchangeGpos(Receiver *receiver, Source *source)
{
	receiver->stats.gpos[0] = source->stats.gpos[0];
	receiver->stats.gpos[1] = source->stats.gpos[1];
	receiver->stats.gpos[2] = source->stats.gpos[2];
}
template <typename Receiver, typename Source>
void exchangeGpos(Receiver receiver, Source *source)
{
	receiver.stats.gpos[0] = source->stats.gpos[0];
	receiver.stats.gpos[1] = source->stats.gpos[1];
	receiver.stats.gpos[2] = source->stats.gpos[2];
}
//***************************************
//***************************************
//
// Drawing section, including distance
// checkers and some other stuff
//
//***************************************
//***************************************
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
	if (checkPlayerDistanceOType(otype, g, g->g_xres/2,g->g_yres/2)) {
		float xdist, ydist;
		xdist = p.stats.spos[0] + (stats.gpos[0] - p.stats.gpos[0] - stats.width);
		ydist = p.stats.spos[1] + (stats.gpos[1] - p.stats.gpos[1] - stats.height);
		otype.draw(xdist, ydist, stats);
	}
}

// Specialization for pointer objects
template <typename OType>
void drawOType(OType *otype, Game *g)
{
	Player p = g->Player_1;
	Stats stats;
	stats = otype->stats;
	if (checkPlayerDistanceOType(otype, g, g->g_xres/2,g->g_yres/2)) {
		float xdist, ydist;
		xdist = p.stats.spos[0] + (stats.gpos[0] - p.stats.gpos[0] - stats.width);
		ydist = p.stats.spos[1] + (stats.gpos[1] - p.stats.gpos[1] - stats.height);
		otype->draw(xdist, ydist, stats);
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

template <typename OType>
void updateObjGposStat(OType otype)
{
	otype.stats.gpos[0] = otype.stats.gpos[0] + otype.stats.vel[0];
	otype.stats.gpos[1] = otype.stats.gpos[1] + otype.stats.vel[1];
}
template <typename OType>
void updateObjGposStat(OType *otype)
{
	otype->stats.gpos[0] = otype->stats.gpos[0] + otype->stats.vel[0];
	otype->stats.gpos[1] = otype->stats.gpos[1] + otype->stats.vel[1];
}
//
//
//
#endif
