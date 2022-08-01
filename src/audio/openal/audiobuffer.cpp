#include "audiobuffer.h"
#include <AL/al.h>


#include <iostream>



#include "aldebug.h"

#include "../waveloader.h"


//#define OLD_CODE
namespace archt {
	
	AudioBuffer::AudioBuffer() {

		
	}

	AudioBuffer::AudioBuffer(const std::string& path) :file(path) {
	


		WaveHeader header;
		uint16_t* buffer = loadWaveFile(path, header);

		AL_CALL(alGenBuffers(1, &id));
		AL_CALL(alBufferData(id, AL_FORMAT_STEREO16, buffer, header.dataSize, header.samplerate));


		delete[] buffer;


	}

	AudioBuffer::~AudioBuffer() {

	}

}