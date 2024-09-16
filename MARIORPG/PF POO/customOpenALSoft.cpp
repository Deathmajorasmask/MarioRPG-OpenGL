#include "customOpenALSoft.h"

//Manual https://github.com/kcat/openal-soft/wiki/Programmer%27s-Guide
//OpenAL error checking
#define OpenAL_ErrorCheck(message)\
{\
	ALenum error = alGetError();\
	if( error != AL_NO_ERROR)\
	{\
		std::cerr << "OpenAL Error: " << error << " with call for " << #message << std::endl;\
	}\
}

#define alec(FUNCTION_CALL)\
FUNCTION_CALL;\
OpenAL_ErrorCheck(FUNCTION_CALL)

#define ENABLE_NO_GPL_MAIN 1
#if ENABLE_NO_GPL_MAIN
customOpenALSoft::customOpenALSoft()
{
	if (!device)
	{
		std::cerr << "failed to get the default device for OpenAL" << std::endl;
		// return -1;
	}
	std::cout << "OpenAL Device: " << alcGetString(device, ALC_DEVICE_SPECIFIER) << std::endl;
	//OpenAL_ErrorCheck(device);
	// 
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Activate this context so that OpenAL state modifications are applied to the context
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (!alcMakeContextCurrent(context))
	{
		std::cerr << "failed to make the OpenAL context the current context" << std::endl;
		// return -1;
	}
	//OpenAL_ErrorCheck("Make context current");

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create a listener in 3d space (ie the player); (there always exists as listener, you just configure data on it)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alListener3f(AL_POSITION, 0.f, 0.f, 0.f));
	alec(alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f));
	ALfloat forwardAndUpVectors[] = {
		/*forward = */ 1.f, 0.f, 0.f,
		/* up = */ 0.f, 1.f, 0.f
	};
	alec(alListenerfv(AL_ORIENTATION, forwardAndUpVectors));

}

customOpenALSoft::~customOpenALSoft()
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// clean up our resources!
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alDeleteSources(1, &monoSource));
	alec(alDeleteSources(1, &stereoSource));
	alec(alDeleteBuffers(1, &monoSoundBuffer));
	alec(alDeleteBuffers(1, &stereoSoundBuffer));
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context);
	alcCloseDevice(device);
}

int customOpenALSoft::customOALSSoundMono(std::string dirFileWav, float volumeGain, bool loopSound, float Velx, float Vely, float Velz, float Posx, float Posy, float Posz) {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Create buffers that hold our sound data; these are shared between contexts and ar defined at a device level
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char* char_arr = &dirFileWav[0];
	{
		drwav_int16* pSampleData = drwav_open_file_and_read_pcm_frames_s16(char_arr, &monoData.channels, &monoData.sampleRate, &monoData.totalPCMFrameCount, nullptr);
		if (pSampleData == NULL) {
			std::cerr << "failed to load audio file" << std::endl;
			drwav_free(pSampleData, nullptr); //todo use raii to clean this up
			return -1;
		}
		if (monoData.getTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max()))
		{
			std::cerr << "too much data in file for 32bit addressed vector" << std::endl;
			drwav_free(pSampleData, nullptr);
			return -1;
		}
		monoData.pcmData.resize(size_t(monoData.getTotalSamples()));
		std::memcpy(monoData.pcmData.data(), pSampleData, monoData.pcmData.size() * /*twobytes_in_s16*/2);
		drwav_free(pSampleData, nullptr);
	}

	alec(alGenBuffers(1, &monoSoundBuffer));
	alec(alBufferData(monoSoundBuffer, monoData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, monoData.pcmData.data(), monoData.pcmData.size() * 2 /*two bytes per sample*/, monoData.sampleRate));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// create a sound source that plays our mono sound (from the sound buffer)
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	alec(alGenSources(1, &monoSource));
	alec(alSource3f(monoSource, AL_POSITION, Posx, Posy, Posz));
	alec(alSource3f(monoSource, AL_VELOCITY, Velx, Vely, Velz));
	alec(alSourcef(monoSource, AL_PITCH, 1.0f));
	alec(alSourcef(monoSource, AL_GAIN, volumeGain));
	if (loopSound) {
		alec(alSourcei(monoSource, AL_LOOPING, AL_TRUE));
	}
	else {
		alec(alSourcei(monoSource, AL_LOOPING, AL_FALSE));
	}
	alec(alSourcei(monoSource, AL_BUFFER, monoSoundBuffer));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// play the mono sound source
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alSourcePlay(monoSource));
	alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));

	return 1;
}

int customOpenALSoft::customOALSSoundMonoBucle() {

	if (sourceState == AL_PLAYING)
	{
		//basically loop until we're done playing the mono sound source
		alec(alGetSourcei(monoSource, AL_SOURCE_STATE, &sourceState));
		return 1; // AL_PLAYING TRUE
	}

	return 0; // AL_PLAYING FALSE
}

int customOpenALSoft::customOALSSoundMonoStop() {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// clean up our resources!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		alec(alDeleteSources(1, &monoSource));
		alec(alDeleteBuffers(1, &monoSoundBuffer));
		return 1;
}

int customOpenALSoft::customOALSSoundStereo(std::string dirFileWav, float volumeGain, bool loopSound) {

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// load a stereo file into a buffer
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char* char_arr = &dirFileWav[0];
	{
		drwav_int16* pSampleData = drwav_open_file_and_read_pcm_frames_s16(char_arr, &stereoData.channels, &stereoData.sampleRate, &stereoData.totalPCMFrameCount, nullptr);
		if (pSampleData == NULL) {
			std::cerr << "failed to load audio file" << std::endl;
			return -1;
		}
		if (stereoData.getTotalSamples() > drwav_uint64(std::numeric_limits<size_t>::max()))
		{
			std::cerr << "too much data in file for 32bit addressed vector" << std::endl;
			return -1;
		}
		stereoData.pcmData.resize(size_t(stereoData.getTotalSamples()));
		std::memcpy(stereoData.pcmData.data(), pSampleData, stereoData.pcmData.size() * /*twobytes_in_s15*/2);
		drwav_free(pSampleData, nullptr);
	}

	alec(alGenBuffers(1, &stereoSoundBuffer));
	alec(alBufferData(stereoSoundBuffer, stereoData.channels > 1 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, stereoData.pcmData.data(), stereoData.pcmData.size() * 2 /*two bytes per sample*/, stereoData.sampleRate));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// create a sound source for our stereo sound; note 3d positioning doesn't work with stereo files because
	// stereo files are typically used for music. stereo files come out of both ears so it is hard to know
	// what the sound should be doing based on 3d position data.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	alec(alGenSources(1, &stereoSource));
	//alec(alSource3f(stereoSource, AL_POSITION, 0.f, 0.f, 1.f)); //NOTE: this does not work like mono sound positions!
	//alec(alSource3f(stereoSource, AL_VELOCITY, 0.f, 0.f, 0.f)); 
	alec(alSourcef(stereoSource, AL_PITCH, 1.f));
	alec(alSourcef(stereoSource, AL_GAIN, volumeGain));
	if (loopSound) {
		alec(alSourcei(stereoSource, AL_LOOPING, AL_TRUE));
	}
	else {
		alec(alSourcei(stereoSource, AL_LOOPING, AL_FALSE));
	}
	alec(alSourcei(stereoSource, AL_BUFFER, stereoSoundBuffer));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// play the stereo sound source after the mono!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	alec(alSourcePlay(stereoSource));
	alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));

	return 1;
}

int customOpenALSoft::customOALSSoundStereoBucle() {

	if (sourceState == AL_PLAYING)
	{
		//basically loop until we're done playing the mono sound source
		alec(alGetSourcei(stereoSource, AL_SOURCE_STATE, &sourceState));
		return 1; // AL_PLAYING TRUE
	}

	return 0; // AL_PLAYING FALSE
}

int customOpenALSoft::customOALSSoundStereoStop() {
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// clean up our resources!
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	alec(alDeleteSources(1, &stereoSource));
	alec(alDeleteBuffers(1, &stereoSoundBuffer));
	return 1;
}

#endif // ENABLE_NO_GPL_MAIN