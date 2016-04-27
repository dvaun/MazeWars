#include "Player.h"
#include "Weapon.h"


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
