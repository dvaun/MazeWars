#ifndef ROSEP_CPP
#define ROSEP_CPP

// Name: Rose Phannavong
// Written: 27 April 2016
// Modified: 28 April 2016
// Description: The code will be implementing sound/music for the game.
// Sound affects when the player uses the weapon.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>

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

    //Create a buffer to hold sound information.
    ALuint alBuffer;
    alBuffer = alutCreateBufferFromFile("./pewpew.wav");

    ALuint alSource;
    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    
    //Set volume and pitch.
    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    //No looping for sound.
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }
    for (int i = 0; i < 4; i++) {
        alSourcePlay(alSource);
        usleep(250000);
    }

    //First we must delete the source.
    alDeleteSources(1, &alSource);
    
    //Second we must delete the buffer.
    alDeleteBuffers(1, &alBuffer);

    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);

}

#endif
