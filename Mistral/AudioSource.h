#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <fstream>

#include "OpenAl/include/al.h"
#include "OpenAL/include/alc.h"
#include "OpenAL/include/efx.h"
#include "OpenAL/include/efx-creative.h"
#include "OpenAL/include/EFX-Util.h"
#include "OpenAL/include/xram.h"

class AudioSource {
public:
	AudioSource() {
		alGenSources(1, &sourceID);
		alSourcef(sourceID, AL_GAIN, 1);
		alSourcef(sourceID, AL_PITCH, 1);
		alSource3f(sourceID, AL_POSITION, 0, 0, 0);

	}

	void playSound(unsigned int bufferid) {
		stop();
		alSourcei(sourceID, AL_BUFFER, bufferid);
		alSourcePlay(sourceID);
	}

	void setVolume(float volume) {
		alSourcef(sourceID, AL_GAIN, volume);
	}

	void setPosition(float x, float y, float z) {
		alSource3f(sourceID, AL_POSITION, x, y, z);
	}

	void setVelocity(float x, float y, float z) {
		alSource3f(sourceID, AL_VELOCITY, x, y, z);
	}

	void setLooping(bool loop) {
		alSourcei(sourceID, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}

	void pause() {
		alSourcePause(sourceID);
	}


	void continuePlaying() {
		alSourcePlay(sourceID);
	}


	void stop() {
		alSourceStop(sourceID);
	}


	~AudioSource() {
		/*ALCcontext* context = alcGetCurrentContext();
		ALCdevice* device = alcGetContextsDevice(context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);*/
		stop();
		alDeleteSources(1, &sourceID);
	}

private:
	unsigned int sourceID;


};