#include "audiobuffer.h"
#include <AL/al.h>
#include <sndlib/sndfile.h>

#include <iostream>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>
#include <AL/efx-creative.h>
#include <AL/EFX-Util.h>
#include <AL/xram.h>

namespace archt {
	
	AudioBuffer::AudioBuffer() {

		
	}

	AudioBuffer::AudioBuffer(const std::string& path) {
		
		SNDFILE* soundFile;
		SF_INFO info;
		soundFile = sf_open(path.c_str(), SFM_READ, &info);
		
		if (!soundFile) {
			printf("Failed to open sound file: %s\n", path.c_str());
			__debugbreak();
		}
		else if (info.frames < 1 || info.frames >(sf_count_t) (INT_MAX / sizeof(short) / info.channels)) {
			printf("Bad sample count in %s\n", path.c_str());
			__debugbreak();
		}


		short* buffer;
		sf_count_t frameCount;
		int bytes;
		ALenum format = AL_NONE;

		if (info.channels == 1) {
			format = AL_FORMAT_MONO16;
		}
		else if (info.channels == 2) {
			format = AL_FORMAT_STEREO16;
		}
		/*else if (info.channels == 3 &&
				 sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			format = AL_FORMAT_BFORMAT2D_16;
		}
		else if (info.channels == 4 &&
					sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT) {
			format = AL_FORMAT_BFORMAT3D_16; 
		}
		*/
		if (format == AL_NONE) {
			__debugbreak();
		}

		buffer = (short*) malloc((size_t) (info.frames * info.channels) * sizeof(short));
		frameCount = sf_read_short(soundFile, buffer, info.frames);

		if (frameCount < 1) {
			free(buffer);
			sf_close(soundFile);
			printf("Failed to read sound file : %s\n", path.c_str());
			__debugbreak();
		}

		bytes = (ALsizei) (frameCount * info.channels) * (ALsizei) (sizeof(short));

		alGenBuffers(1, &id);
		alBufferData(id, format, buffer, bytes, info.samplerate);

		free(buffer);
		sf_close(soundFile);

		ALenum error = alGetError();
		if (error != AL_NO_ERROR) {
			printf("OpenAL error:\n%s\n", alGetString(error));
			
			if (id && alIsBuffer(id))
				alDeleteBuffers(1, &id);
			
			__debugbreak();
		}

	}


}