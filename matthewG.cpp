/* Name: Matthew Gaitan
 * Date: April 27, 2016
 * Last Modified: May 3, 2016
 * Description: My code handles all of the character movement if a controller 
 * is being used. In the main mazewars.cpp file, the current values for the
 * buttons as well as joysticks are added to an array and those values are
 * later passed to my checkController function. My checkController function
 * does whatever action that relates to the button or joystick being updated.
 */

#include "game.h"
#include <cmath>

void movement(Game *g) 
{
	Flt rad = ((g->Player_1.angle+90.0f) / 360.0f) * M_PI * 2.0f;
	
	Flt xdir = cos(rad);
	Flt ydir = sin(rad);

	g->Player_1.vel[0] = xdir*2.0f;
	g->Player_1.vel[1] = ydir*2.0f;
}

void checkController(int axis[], Game *g)
{	
	//Check Controller 

	//calculated myself instead of using Vec + normalize
	//Vec + normalize didn't work as intended
	float x = axis[0]/32767.0;	
	float y = -axis[1]/32767.0;
	
	//	std::cout << "x: " << x << std::endl;
	//	std::cout << "y: " << y << std::endl;
	float twoPos = sqrt(2 + sqrt(2))/2.0; //.9238
	float twoNeg = sqrt(2 - sqrt(2))/2.0; //.3827
	//std::cout << "twoPos: " << twoPos << std::endl;
	//std::cout << "twoNeg: " << twoNeg << std::endl;

	//Up and Left
	if (x >= -twoPos+.08 && x <= -twoNeg+.08 && 
		y >= twoNeg-.08 && y <= twoPos+.08) {
		g->Player_1.angle = 45.0f;
		movement(g);
	}
	//Up and Right
	else if (x >= twoNeg+.08 && x <= twoPos+.08 && 
			y <= twoPos+.08 && y >= twoNeg-.08) { 
		g->Player_1.angle = -45.0f;
		movement(g);
	}
	//Left and Down	
	else if (x >= -twoPos+.08 && x <= -twoNeg-.08 && 
			y <= -twoNeg-.08 && y >= -twoPos+.08) {
		g->Player_1.angle = 135.0f;
		movement(g);
	}
	//Down and Right
	else if (x >= twoNeg-.08 && x <= twoPos+.08 && 
			y >= -twoPos+.08 && y <= -twoNeg-.08) {
		g->Player_1.angle = 225.0f;
		movement(g);
	}
	//Up
	else if (x <= twoNeg+.08 && x >= -twoNeg-.08 && y >= twoPos-.08 ) {  
		g->Player_1.angle = 0.0f;
		movement(g);
	}
	//Left
	else if (x <= -twoPos+.08 && y <= twoNeg+.08 && y >= -twoNeg+.08) {
		g->Player_1.angle = 90.0f;
		movement(g);
	}
	//Down
	else if(fabs(x) <= twoNeg+.08 && -fabs(y) <= -twoPos+.08) {
		g->Player_1.angle = 180.0f;
		movement(g);
	}
	//Right
	else if (x >= twoPos-.08 && y <= twoNeg+.08 && y >= -twoNeg+.08) {
		g->Player_1.angle = 270.0f;
		movement(g);
	}
	else {
		g->Player_1.vel[0] = 0;
		g->Player_1.vel[1] = 0;
	}
}
