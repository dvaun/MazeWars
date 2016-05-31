#ifndef ROSEP_CPP
#define ROSEP_CPP

// Name: Rose Phannavong
// Written: 27 April 2016
// Modified: 30 May 2016
// Description: The code will be implementing sound/music for the game.

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <GL/glx.h>
#include <stdlib.h>
#include </usr/include/AL/alut.h>
#include <cmath>
#include "game_objects.h"
ALuint alSource[10];
ALuint alBuffer[10];

void init_sounds()
{
    //Check and clear.
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: alutInit()\n");
    }
    alGetError();

    //Setup the listener, used forward and up vectors.
    float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

}

void release_sounds()
{
    //First we must delete the source.
    alDeleteSources(1, &alSource[0]);
    alDeleteSources(1, &alSource[1]);
    alDeleteSources(1, &alSource[2]);

    //Second we must delete the buffer.
    alDeleteBuffers(1, &alBuffer[0]);
    alDeleteBuffers(1, &alBuffer[1]);
    alDeleteBuffers(1, &alBuffer[2]);

    //Get active context and device for active context.
    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);

    //Disable and release context.
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);

    //Close device.
    alcCloseDevice(Device);
}

void load_sounds()
{
    //Bullet sound.
    alBuffer[0] = alutCreateBufferFromFile("./sound/bang.wav");
    alGenSources(1, &alSource[0]);
    alSourcei(alSource[0], AL_BUFFER, alBuffer[0]);

    //Death sound.
    alBuffer[1] = alutCreateBufferFromFile("./sound/male_death.wav");
    alGenSources(1, &alSource[1]);
    alSourcei(alSource[1], AL_BUFFER, alBuffer[1]);

    //Walk sound.
    alBuffer[2] = alutCreateBufferFromFile("./sound/walk.wav");
    alGenSources(1, &alSource[2]);
    alSourcei(alSource[2], AL_BUFFER, alBuffer[2]);
    
    //Death sound.
    alBuffer[3] = alutCreateBufferFromFile("./sound/3107.wav");
    alGenSources(1, &alSource[3]);
    alSourcei(alSource[3], AL_BUFFER, alBuffer[3]);

    //Background Pause music.
    alBuffer[4] = alutCreateBufferFromFile("./sound/bensound-epic.wav");
    alGenSources(1, &alSource[4]);
    alSourcei(alSource[4], AL_BUFFER, alBuffer[4]);

    //Falling boulders sound.
    alBuffer[5] = alutCreateBufferFromFile("./sound/Rock_Slide-000.wav");
    alGenSources(1, &alSource[5]);
    alSourcei(alSource[5], AL_BUFFER, alBuffer[5]);
    
    //Background music.
    alBuffer[6] = alutCreateBufferFromFile("./sound/parabolix_cavern.wav");
    alGenSources(1, &alSource[6]);
    alSourcei(alSource[6], AL_BUFFER, alBuffer[6]);
 
}

void play_sounds(int soundOption)
{
    //Set volume and pitch.
    alSourcef(alSource[soundOption], AL_GAIN, 1.0f);
    alSourcef(alSource[soundOption], AL_PITCH, 1.0f);
    alSourcei(alSource[soundOption], AL_LOOPING, AL_FALSE);

    //No looping for sound.
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }
    alSourcePlay(alSource[soundOption]);
}

void bubblez(int radius, int x, int y, float red, float green, float blue)
{
    static int num = 0;
    std::cout << "circle num: " << num++ << std::endl;
    glColor3f(red, green, blue);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_POINTS);

    //Randomly get a quadrant.
    int quadrant = rand() % 4 + 1;
    switch (quadrant) {
        case(1):
            x += rand() % 150;
            y += rand() % 150;
            break;
        case(2):
            x -= rand() % 150;
            y += rand() % 150;
            break;
        case(3):
            x -= rand() % 150;
            y -= rand() % 150;
            break;
        case(4):
            x += rand() % 150;
            y -= rand() % 150;
            break;
    }
    for (float i = 0.0; i < 360.0; i+=1.0) {
         glVertex2f(radius * cos(i) + x, radius * sin(i) + y);
    } 
    glEnd();
    //glDisable(GL_BLEND);
    glDisable(GL_POINT_SMOOTH);
}

void pressR(Game *g)
{
    //Special keystroke for bubbles.
    std::cout << "R pressed" << std::endl;
    srand(NULL);
    int x = g->Player_1.stats.spos[0];
    int y = g->Player_1.stats.spos[1];

    int numBubbles = 10;
    for (int i = 0; i < numBubbles; i++) {
	int radius = rand() % 20 + 10;
	float red = rand() * 10;
	float green = rand() * 15;
	float blue = rand() * 20;
        bubblez(radius, x, y, red, green, blue);
    }
}

#endif
