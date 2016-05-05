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
