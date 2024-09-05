#pragma once

#include<iostream>
#include<AL/al.h> // https://github.com/kcat/openal-soft
#include<AL/alc.h>
#include<dr_lib/dr_wav.h> // https://github.com/mackron/dr_libs/tree/master
#include <vector>

class customOpenALSoft
{
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// find the default audio device
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	const ALCchar* defaultDeviceString = alcGetString(/*device*/nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
	ALCdevice* device = alcOpenDevice(defaultDeviceString);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create an OpenAL audio context from the device
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ALCcontext* context = alcCreateContext(device, /*attrlist*/ nullptr);
	//OpenAL_ErrorCheck(context);

	struct ReadWavData
	{
		unsigned int channels = 0;
		unsigned int sampleRate = 0;
		drwav_uint64 totalPCMFrameCount = 0;
		std::vector<uint16_t> pcmData;
		drwav_uint64 getTotalSamples() { return totalPCMFrameCount * channels; }
	};
	ReadWavData monoData;
	ALuint monoSoundBuffer;

	ReadWavData stereoData;
	ALuint stereoSoundBuffer;

	ALuint monoSource;
	ALuint stereoSource;

	ALint sourceState;

	customOpenALSoft();
	~customOpenALSoft();
	int customOALSSoundMono();
	int customOALSSoundMonoBucle();
	int customOALSSoundStereo();
	int customOALSSoundStereoBucle();
private:

};

