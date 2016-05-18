#include "game_objects.h"
#include "joystick.hh"
#include "person.h"
#include <string>
//author: Matthew Gaitan
void getJoystickEvent(JoystickEvent event, int joy[], int axis[]);
void movement(Game *g);
void checkController(int axis[], Game *g);
void checkKeys(int keys[], Game *g);
void renderCrosshair(int axis[], Game *g, bool keyboard);
void renderShield(Game *g);
Ppmimage* characterSelection(std::string characterSelected);
void renderCharacter(Person person, Game *g, float w, int keys[], GLuint personTexture1); 
int renderTitleScreen(GLuint tileTexture, GLuint logoTexture, GLuint boulderTexture, GLuint enterTexture, Ppmimage *logo, Ppmimage *boulders, Ppmimage *enter, int enterPressed);
void resolution(int width, int height);