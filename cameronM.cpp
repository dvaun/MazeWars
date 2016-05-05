/* Name: Cameron Morrow
 * Date: May 04, 2016
 * Last Modified: May 04, 2016
 * Description: My code handles all of the weapon movement if a controller 
 * is not being used.
 * In the mazewars.cpp I modified all of the original asteroids code to remove
 * the engine from the ship and the asteroid field, also changed the window title
 * 
 
void pointPlayer(Game *g)
{
	//Make the player point at the cursor
	g->gun.pos[0] = g->Player_1.pos[0];
	g->gun.pos[1] = g->Player_1.pos[1];
	float weaponx = g->gun.pos[0];
	float weapony = g->gun.pos[1];

	float nDeg = atan(((yres-savey)-(weapony))/((savex)-(weaponx))) * 180 / PI;

    if (savex > weaponx && (yres - savey) > weapony)
		nDeg += 180;
	if (savex > weaponx && (yres - savey) < weapony)
		nDeg -= 180;
	if (g->gun.angle >= 360.f)
		g->gun.angle -= 360.0f;
	if (g->gun.angle <= 360.0f){
 		if (nDeg > 270)
			nDeg -= 360;
		g->gun.angle = nDeg + 90;
	}
	if (g->gun.angle < 0.0f)
		g->gun.angle += 360.0f;
}
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
int *res;

void getScreenRes(int x, int y)
{
	res = new int[2];
	res[0] = x;
	res[1] = y;
}
void drawHealth(Player x)
{
    //Background of health bar
	glColor3ub(255, 0, 0);
	glPushMatrix();
	glTranslatef(res[0]-150, 50, 0);
	glBegin(GL_QUADS);
		glVertex2i(-100, -15);
		glVertex2i(-100, 15);
		glVertex2i(100, 15);
		glVertex2i(100, -15);
	glEnd();
	glPopMatrix();

	//remaining health
	int remaining = 100 - x.Current_Health;
	glColor3ub(0, 255, 0);
        glPushMatrix();
        glTranslatef((res[0]-150)-remaining, 50, 0);
        glBegin(GL_QUADS);
                glVertex2i(-(100 - remaining), -15);
                glVertex2i(-(100 - remaining), 15);
                glVertex2i((100 - remaining), 15);
                glVertex2i((100 - remaining), -15);
        glEnd();
        glPopMatrix();

	Rect r;
	//
	r.bot = 20;
	r.left = res[0] - 200;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ffffff, "Total Health: %i", x.Max_Health);
	if(x.Current_Health <= 50){
            ggprint8b(&r, 16, 0x00ff0000, "Remaining Health: %i", x.Current_Health);
        }else{
            ggprint8b(&r, 16, 0x0000ff00, "Remaining Health: %i", x.Current_Health);
        }
}
void drawAmmo(Player x){
    //Background of ammo bar
        glColor3ub(255, 0, 0);
        glPushMatrix();
        glTranslatef(res[0]-150, 150, 0);
        glBegin(GL_QUADS);
                glVertex2i(-100, -15);
                glVertex2i(-100, 15);
                glVertex2i(100, 15);
                glVertex2i(100, -15);
        glEnd();
        glPopMatrix();

        //remaining health
        int remaining = 100 - x.Current_Ammo;
        glColor3ub(0, 0, 255);
        glPushMatrix();
        glTranslatef((res[0]-150)-remaining, 150, 0);
        glBegin(GL_QUADS);
                glVertex2i(-(100 - remaining), -15);
                glVertex2i(-(100 - remaining), 15);
                glVertex2i((100 - remaining), 15);
                glVertex2i((100 - remaining), -15);
        glEnd();
        glPopMatrix();
	
        Rect r;
        //
        r.bot = 120;
        r.left = res[0] - 200;
        r.center = 0;
        ggprint8b(&r, 16, 0x00ffffff, "Total Ammo: %i", x.Max_Ammo);
        if(x.Current_Ammo <= 50){
	    ggprint8b(&r, 16, 0x00ff0000, "Remaining Ammo: %i", x.Current_Ammo);
	}else{
	    ggprint8b(&r, 16, 0x0000ff00, "Remaining Ammor: %i", x.Current_Ammo);
	}
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
	x->pos[0] = 40;
	x->pos[1] = 40;
	VecZero(x->vel);
	VecZero(x->dir);
}
void drawHealthPack(HealthPack HP)
{
	glColor3ub(0, 255, 0);
        glPushMatrix();
        glTranslatef(HP.pos[0], HP.pos[1], HP.pos[1]);
        glBegin(GL_QUADS);
                glVertex2i(-20, -8);
                glVertex2i(-20, 8);
                glVertex2i(20, 8);
                glVertex2i(20, -8);
        glEnd();
        glPopMatrix();
	Rect r;
        //
        r.bot = HP.pos[1]-5;
        r.left = HP.pos[0]-17;
        r.center = 0;
        ggprint8b(&r, 16, 0x00000000, "Health");
}
