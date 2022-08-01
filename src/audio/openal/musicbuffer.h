#pragma once
/*#include "albuffer.h"

#include <AL/al.h>
#include <sndlib/sndfile.h>

#include <string>

#define MAX_MUSIC_BUFFERS 4

namespace archt {

	class MusicBuffer : public ALBuffer {


		uint32_t* id = new uint32_t[MAX_MUSIC_BUFFERS];
		std::string path;
		SNDFILE* file = nullptr;
		SF_INFO info;
		size_t frames = 0;
		ALsizei bytes = 0;
		int format = 0;
		int bufferCount = 0;
		const int samples = 800 * 1024;
		int16_t* buffer = nullptr;

	public:
		MusicBuffer();
		MusicBuffer(const std::string& path);
		~MusicBuffer();

		int attachToSource();

		int updateBufferStream(uint32_t srcId);

		inline uint32_t* getId() const { return id; }
	};


}*/