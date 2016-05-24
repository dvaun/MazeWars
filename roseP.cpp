#ifndef ROSEP_CPP
#define ROSEP_CPP

// Name: Rose Phannavong
// Written: 27 April 2016
// Modified: 15 May 2016
// Description: The code will be implementing sound/music for the game.
// Sound affects when the player uses the weapon.

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>

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

    //Background music
    alBuffer[4] = alutCreateBufferFromFile("./sound/bensound-epic.wav");
    alGenSources(1, &alSource[4]);
    alSourcei(alSource[4], AL_BUFFER, alBuffer[4]);
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

#endif
