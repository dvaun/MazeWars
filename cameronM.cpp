#ifndef CAMERON_CPP
#define CAMERON_CPP
/* Name: Cameron Morrow
* Date: May 04, 2016
* Last Modified: May 13, 2016
* Description: My code handles all of the weapon movement if a controller 
* is not being used.
* In the mazewars.cpp I modified all of the original asteroids code to remove
* the engine from the ship and the asteroid field, also changed the window title
* I am drawing and handling the health bar and "HUD" 
*/
int *res;
void getScreenRes(int x, int y)
{
	res = new int[2];
	res[0] = x;
	res[1] = y;
}
void pointPlayer(Game *g, int savex, int savey)
{
	//Make the player's gun point at the cursor
	exchangeGpos(&g->gun, &g->Player_1);
	float weaponx = g->Player_1.stats.spos[0];
	float weapony = g->Player_1.stats.spos[1];

	float nDeg = atan(((res[1]-savey)-(weapony))/\
	((savex)-(weaponx))) * 180 / 3.1415926;

	if (savex > weaponx && (res[1] - savey) > weapony)
		nDeg += 180;
	if (savex > weaponx && (res[1] - savey) < weapony)
		nDeg -= 180;

	if (g->gun.stats.angle > 360.f) {
		g->gun.stats.angle = 360.0f;
	}
	if (g->gun.stats.angle <= 360.0f) {
		if (nDeg > 270){
			nDeg -= 360;
		}
		g->gun.stats.angle = nDeg + 90;
	}
	if (g->gun.stats.angle < 0.0f) {
		g->gun.stats.angle += 360.0f;
	}
}
void drawHUD(Player x)
{
	drawBackground();
	drawHealth(x);
	drawAmmo(x);
	drawArtifacts(x);
	switch (x.lives) {
		case 4:
			drawLives(10, 0);
		case 3:
			drawLives(50, 0);
		case 2:
			drawLives(10, -30);
		case 1:
			drawLives(50, -30);
	}
}
void drawBackground()
{
	glColor3ub(47, 47, 47);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glColor3ub(47, 47, 47);
	glVertex2i(0, 0);
	glColor3ub(84, 84, 84);
	glVertex2i(-350, 0);
	glColor3ub(48, 48, 48);
	glVertex2i(-350, 120);
	glColor3ub(54, 54, 54);
	glVertex2i(-320, 150);
	glColor3ub(84, 84, 84);
	glVertex2i(0, 150);
	glEnd();
	glPopMatrix();

	glColor3ub(54, 54, 54);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-340, 10);
	glVertex2i(-350, 0);
	glVertex2i(-350, 120);
	glVertex2i(-340, 115);
	glEnd();
	glPopMatrix();

	glColor3ub(179, 179, 179);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-340, 115);
	glVertex2i(-350, 120);
	glVertex2i(-320, 150);
	glVertex2i(-315, 140);
	glEnd();
	glPopMatrix();

	glColor3ub(152, 152, 152);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-315, 140);
	glVertex2i(-320, 150);
	glVertex2i(0, 150);
	glVertex2i(-15, 140);
	glEnd();
	glPopMatrix();

	glColor3ub(12, 12, 12);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-15, 140);
	glVertex2i(0, 150);
	glVertex2i(0, 0);
	glVertex2i(-15,10);
	glEnd();
	glPopMatrix();

	glColor3ub(12, 12, 12);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(0, 0);
	glVertex2i(-350, 0);
	glVertex2i(-340, 10);
	glVertex2i(-15, 10);
	glEnd();
	glPopMatrix();	
}
void drawDiamondBack(int x)
{
	glColor3ub(17, 17, 17);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-315+x, 40);
	glVertex2i(-330+x, 40);
	glVertex2i(-310+x, 60);
	glVertex2i(-310+x, 45);
	glEnd();
	glPopMatrix();

	glColor3ub(36, 36, 36);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-310+x, 45);
	glVertex2i(-310+x, 60);
	glVertex2i(-290+x, 40);
	glVertex2i(-305+x, 40);
	glEnd();
	glPopMatrix();

	glColor3ub(142, 142, 142);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-305+x, 40);
	glVertex2i(-290+x, 40);
	glVertex2i(-310+x, 20);
	glVertex2i(-310+x, 35);
	glEnd();
	glPopMatrix();

	glColor3ub(62, 62, 62);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-310+x, 35);
	glVertex2i(-310+x, 20);
	glVertex2i(-330+x, 40);
	glVertex2i(-315+x, 40);
	glEnd();
	glPopMatrix();
}
void drawDiamond(int x)
{	
	glColor3ub(180, 226, 175);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-320+x, 40);
	glVertex2i(-330+x, 40);
	glVertex2i(-310+x, 60);
	glVertex2i(-310+x, 50);
	glEnd();
	glPopMatrix();

	glColor3ub(40, 126, 35);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-310+x, 50);
	glVertex2i(-310+x, 60);
	glVertex2i(-290+x, 40);
	glVertex2i(-300+x, 40);
	glEnd();
	glPopMatrix();

	glColor3ub(30, 90, 40);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-300+x, 40);
	glVertex2i(-290+x, 40);
	glVertex2i(-310+x, 20);
	glVertex2i(-310+x, 30);
	glEnd();
	glPopMatrix();

	glColor3ub(67, 153, 80);
	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-310+x, 30);
	glVertex2i(-310+x, 20);
	glVertex2i(-330+x, 40);
	glVertex2i(-320+x, 40);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(res[0], 0, 0);
	glBegin(GL_POLYGON);
	glColor3ub(140, 236, 135);
	glVertex2i(-320+x, 40);
	glColor3ub(50, 175, 40);
	glVertex2i(-310+x, 50);
	glColor3ub(140, 236, 135);
	glVertex2i(-300+x, 40);
	glColor3ub(50, 175, 40);
	glVertex2i(-310+x, 30);
	glEnd();
	glPopMatrix();
}
void drawArtifacts(Player x)
{

	if (x.artifact[0]) {
		drawDiamond(80);
	} else {
		drawDiamondBack(80);
	}
	if (x.artifact[1]) {
		drawDiamond(160);
	} else {
		drawDiamondBack(160);
	} 
	if (x.artifact[2]) {
		drawDiamond(240);
	} else {
		drawDiamondBack(240);
	}
	Rect r;
	r.bot = 35;
	r.left = res[0] - 320;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ffffff, "Artifacts:");
}
void drawHealth(Player x)
{
	double remaining = 100-((x.Current_Health/x.Max_Health)*100);
	//Background of health bar
	glPushMatrix();
	glTranslatef(res[0]-150, 85, 0);
	glColor3ub(100, 100, 100);
	glBegin(GL_POLYGON);

	glVertex2i(-90, -15);
	//glColor3ub(240, 110, 110);
	glVertex2i(-100, -5);

	//glColor3ub(240, 110, 110);
	glVertex2i(-100, 5);
	//glColor3ub(230, 20, 20);
	glVertex2i(-90, 15);

	//glColor3ub(230, 20, 20);
	glVertex2i(90, 15);
	//glColor3ub(240, 110, 110);
	glVertex2i(100, 5);

	//glColor3ub(240, 110, 110);
	glVertex2i(100, -5);
	//glColor3ub(230, 20, 20);
	glVertex2i(90, -15);
	glEnd();
	glPopMatrix();

	int test = 10-x.Current_Health;
	if (x.lives > 0) {
		glColor3ub(164, 20, 20);
		glPushMatrix();
		glTranslatef((res[0]-150)-remaining, 85, 0);
		glBegin(GL_POLYGON);
		
		if (100-remaining > 10) {
			glVertex2i(-(90 - remaining), -15);
			glVertex2i(-(100 - remaining), -5);
			glVertex2i(-(100 - remaining), 5);
			glVertex2i(-(90 - remaining), 15);
			glVertex2i((90 - remaining), 15);
			glVertex2i((100 - remaining), 5);
			glVertex2i((100 - remaining), -5);
			glVertex2i((90 - remaining), -15);
		} else {
			glVertex2i(-(90 - remaining + test), -15 + (test));
			glVertex2i(-(100 - remaining), -5);
			glVertex2i(-(100 - remaining), 5);
			glVertex2i(-(90 - remaining + test), 15 - (test));
			glVertex2i((90 - remaining + test), 15 - (test));
			glVertex2i((100 - remaining), 5);
			glVertex2i((100 - remaining), -5);
			glVertex2i((90 - remaining + test), -15 + (test));
		}
		glEnd();
		glPopMatrix();
	}
	Rect r;
	r.bot = 80;
	r.left = res[0] - 240;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ffffff, "Health:");
}
void drawAmmo(Player x){
	double remaining = 100-((x.Current_Ammo/x.Max_Ammo)*100);
	
	//Background of ammo bar
	glColor3ub(100, 100, 100);
	glPushMatrix();
	glTranslatef(res[0]-150, 120, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-90, -15);
	glVertex2i(-100, -5);

	glVertex2i(-100, 5);
	glVertex2i(-90, 15);

	glVertex2i(90, 15);
	glVertex2i(100, 5);

	glVertex2i(100, -5);
	glVertex2i(90, -15);
	glEnd();
	glPopMatrix();
	
	int test = 10-x.Current_Ammo;
	if (100-remaining > 0) {
		glColor3ub(30, 20, 150);
		glPushMatrix();
		glTranslatef((res[0]-150)-remaining, 120, 0);
		glBegin(GL_POLYGON);
		if (100-remaining > 10) {
			glVertex2i(-(90 - remaining), -15);
			glVertex2i(-(100 - remaining), -5);
			glVertex2i(-(100 - remaining), 5);
			glVertex2i(-(90 - remaining), 15);
			glVertex2i((90 - remaining), 15);
			glVertex2i((100 - remaining), 5);
			glVertex2i((100 - remaining), -5);
			glVertex2i((90 - remaining), -15);
		} else {
			glVertex2i(-(90 - remaining + test), -15 + (test));
			glVertex2i(-(100 - remaining), -5);
			glVertex2i(-(100 - remaining), 5);
			glVertex2i(-(90 - remaining + test), 15 - (test));
			glVertex2i((90 - remaining + test), 15 - (test));
			glVertex2i((100 - remaining), 5);
			glVertex2i((100 - remaining), -5);
			glVertex2i((90 - remaining + test), -15 + (test));
		}
		glEnd();
		glPopMatrix();
	}
	Rect r;
	r.bot = 115;
	r.left = res[0] - 240;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ffffff, "Ammo:");
}
void drawLives(int x, int y)
{
	glColor3ub(255, 0, 0);
	glPushMatrix();
	glTranslatef(res[0], 60, 0);
	glBegin(GL_POLYGON);
	glVertex2i(-320+x, 45+y);
	glVertex2i(-330+x, 60+y);
	glVertex2i(-325+x, 65+y);
	glVertex2i(-320+x, 60+y);
	glVertex2i(-315+x, 65+y);
	glVertex2i(-310+x, 60+y);
	glEnd();
	glPopMatrix();
}
void GameOver()
{
	Rect r;
	r.bot = 500;
	r.left = 600;
	r.center = 0;
	ggprint8b(&r, 160, 0x00ff0000, "GAME OVER \n F6 TO RESTART");
}
void Restart(Player *x)
{
	x->Current_Health = 100;
	x->Current_Ammo = 100;
	x->lives = 4;
	x->stats.spos[0] = 625;
	x->stats.spos[1] = 450;
	x->stats.gpos[0] = 500;
	x->stats.gpos[1] = 500;
	x->gameOver = false;
	VecZero(x->stats.dir);
}
void drawHealthPack(int x, int y, int z)
{
	glColor3ub(0, 255, 0);
	glPushMatrix();
	glTranslatef(x, y, z);
	glBegin(GL_QUADS);
	glVertex2i(-20, -8);
	glVertex2i(-20, 8);
	glVertex2i(20, 8);
	glVertex2i(20, -8);
	glEnd();
	glPopMatrix();
	Rect r;
	r.bot = y-5;
	r.left = x-17;
	r.center = 0;
	ggprint8b(&r, 16, 0x00000000, "Health");
}

#endif
