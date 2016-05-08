#include "game_objects.h"
//author: Matthew Gaitan
void getJoystickEvent(JoystickEvent event, int joy[], int axis[]);
void movement(Game *g);
void checkController(int axis[], Game *g);
void checkKeys(int keys[], Game *g);
void renderCrosshair(int axis[], Game *g, bool keyboard);
void renderShield(Game *g);
