#ifndef CAMERON_CPP
#define CAMERON_CPP

/* Name: Cameron Morrow
 * Date: May 04, 2016
 * Last Modified: May 04, 2016
 * Description: My code handles all of the weapon movement if a controller 
 * is not being used.
 * In the mazewars.cpp I modified all of the original asteroids code to remove
 * the engine from the ship and the asteroid field, also changed the window title
 * 
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
        //Make the player point at the cursor
        exchangeGpos(&g->gun, &g->Player_1);
        float weaponx = g->Player_1.stats.spos[0];
        float weapony = g->Player_1.stats.spos[1];

        float nDeg = atan(((res[1]-savey)-(weapony))/\
                ((savex)-(weaponx))) * 180 / 3.1415926;

        if (savex > weaponx && (res[1] - savey) > weapony)
                nDeg += 180;
        if (savex > weaponx && (res[1] - savey) < weapony)
                nDeg -= 180;

        if (g->gun.stats.angle > 360.f)
                g->gun.stats.angle = 360.0f;
        if (g->gun.stats.angle <= 360.0f) {
                if (nDeg > 270)
                        nDeg -= 360;
                g->gun.stats.angle = nDeg + 90;
        }
        if (g->gun.stats.angle < 0.0f)
                g->gun.stats.angle += 360.0f;
}

/*
void MouseCrosshairs()
{
	if(keyboard == true){	
  		float ndeg2 = atan(((900 - savey) - (g->Player_1.pos[1]))/((savex)-(g->Player_1.pos[0]))) * 180/PI;
		if(savex < g->Player_1.pos[0] && (900 - savey) > g->Player_1.pos[1]){
			ndeg2 += 180;
		}
		if(savex < g->Player_1.pos[0] && (900 - savey) < g->Player_1.pos[1]){
			ndeg2 += 180;	    
		}
		crosshair.angle = ndeg2;
	}
}
*/
void drawHUD(Player x)
{

	drawBackground();
	drawHealth(x);
	drawAmmo(x);
	drawArtifacts(x);

}
void drawBackground()
{
	glColor3ub(176, 140, 41);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(0, 0);
                glVertex2i(-350, 0);
		glVertex2i(-350, 120);
                glVertex2i(-320, 150);
                glVertex2i(0, 150);
        glEnd();
        glPopMatrix();

	glColor3ub(179, 144, 49);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-340, 10);
                glVertex2i(-350, 0);
                glVertex2i(-350, 120);
                glVertex2i(-340, 115);
        glEnd();
        glPopMatrix();

	glColor3ub(226, 212, 175);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-340, 115);
                glVertex2i(-350, 120);
                glVertex2i(-320, 150);
                glVertex2i(-315, 140);
        glEnd();
        glPopMatrix();

	glColor3ub(216, 198, 148);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-315, 140);
                glVertex2i(-320, 150);
                glVertex2i(0, 150);
                glVertex2i(-15, 140);
        glEnd();
        glPopMatrix();

	glColor3ub(44, 35, 10);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-15, 140);
                glVertex2i(0, 150);
                glVertex2i(0, 0);
		glVertex2i(-15,10);
        glEnd();
        glPopMatrix();

	glColor3ub(44, 35, 10);
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

glColor3ub(226, 212, 175);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-315+x, 40);
                glVertex2i(-330+x, 40);
                glVertex2i(-310+x, 60);
                glVertex2i(-310+x, 45);
        glEnd();
        glPopMatrix();

        glColor3ub(128, 102, 30);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-310+x, 45);
                glVertex2i(-310+x, 60);
                glVertex2i(-290+x, 40);
                glVertex2i(-305+x, 40);
        glEnd();
        glPopMatrix();

        glColor3ub(44, 35, 10);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-305+x, 40);
                glVertex2i(-290+x, 40);
                glVertex2i(-310+x, 20);
                glVertex2i(-310+x, 35);
        glEnd();
        glPopMatrix();

        glColor3ub(44, 35, 10);
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

        glColor3ub(39, 128, 30);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-310+x, 50);
                glVertex2i(-310+x, 60);
                glVertex2i(-290+x, 40);
                glVertex2i(-300+x, 40);
        glEnd();
        glPopMatrix();

        glColor3ub(13, 44, 10);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-300+x, 40);
                glVertex2i(-290+x, 40);
                glVertex2i(-310+x, 20);
                glVertex2i(-310+x, 30);
        glEnd();
        glPopMatrix();

        glColor3ub(13, 44, 10);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-310+x, 30);
                glVertex2i(-310+x, 20);
                glVertex2i(-330+x, 40);
                glVertex2i(-320+x, 40);
        glEnd();
        glPopMatrix();
        
         glColor3ub(54, 176, 41);
        glPushMatrix();
        glTranslatef(res[0], 0, 0);
        glBegin(GL_POLYGON);
                glVertex2i(-320+x, 40);
                glVertex2i(-310+x, 50);
                glVertex2i(-300+x, 40);
                glVertex2i(-310+x, 30);
        glEnd();
        glPopMatrix();

}
void drawArtifacts(Player x)
{
	if(x.artifact[0]){
	    drawDiamond(80);
	}else{
	    drawDiamondBack(80);
	}
	if(x.artifact[1]){
	    drawDiamond(160);
	}else{
	    drawDiamondBack(160);
	} 
	if(x.artifact[2]){
	    drawDiamond(240);
	}else{
	    drawDiamondBack(240);
	} 
}
void drawHealth(Player x)
{
double remaining = 100-((x.Current_Health/x.Max_Health)*100);
    //Background of health bar
	glColor3ub(255, 0, 0);
	glPushMatrix();
	glTranslatef(res[0]-150, 85, 0);
	glBegin(GL_QUADS);
		glVertex2i(-100, -15);
		glVertex2i(-100, 15);
		glVertex2i(100, 15);
		glVertex2i(100, -15);
	glEnd();
	glPopMatrix();

	//remaining health
	//int remaining = 100 - x.Current_Health;
	glColor3ub(0, 255, 0);
        glPushMatrix();
        glTranslatef((res[0]-150)-remaining, 85, 0);
        glBegin(GL_QUADS);
                glVertex2i(-(100 - remaining), -15);
                glVertex2i(-(100 - remaining), 15);
                glVertex2i((100 - remaining), 15);
                glVertex2i((100 - remaining), -15);
        glEnd();
        glPopMatrix();

	Rect r;
	//
	r.bot = 75;
	r.left = res[0] - 310;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ffffff, "Health:");
}
void drawAmmo(Player x){
    //Background of ammo bar
        glColor3ub(255, 0, 0);
        glPushMatrix();
        glTranslatef(res[0]-150, 120, 0);
        glBegin(GL_QUADS);
                glVertex2i(-100, -15);
                glVertex2i(-100, 15);
                glVertex2i(100, 15);
                glVertex2i(100, -15);
        glEnd();
        glPopMatrix();

        //remaining ammo
        int remaining = 100 - x.Current_Ammo;
        glColor3ub(0, 0, 255);
        glPushMatrix();
        glTranslatef((res[0]-150)-remaining, 120, 0);
        glBegin(GL_QUADS);
                glVertex2i(-(100 - remaining), -15);
                glVertex2i(-(100 - remaining), 15);
                glVertex2i((100 - remaining), 15);
                glVertex2i((100 - remaining), -15);
        glEnd();
        glPopMatrix();
	
        Rect r;
        //
        r.bot = 110;
        r.left = res[0] - 310;
        r.center = 0;
        ggprint8b(&r, 16, 0x00ffffff, "Ammo:");
}
void GameOver(){
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
	x->stats.spos[0] = 625;
	x->stats.spos[1] = 450;
	x->stats.gpos[0] = 500;
	x->stats.gpos[1] = 500;
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
        //
        r.bot = y-5;
        r.left = x-17;
        r.center = 0;
        ggprint8b(&r, 16, 0x00000000, "Health");
}

#endif
