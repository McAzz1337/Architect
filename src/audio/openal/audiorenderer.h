#pragma once

#include "audiobuffer.h"
#include "soundsource.h"


#include <vector>

namespace archt {

	class AudioRenderer {

		static const int MAX_SOUND_SOURCES;
		static const int MAX_BUFFERS;

		static int currentInsert;
		static int currentBuffer;

		static SoundSource** soundSources;
		static std::vector<AudioBuffer*> bufferQueue;


	public:
		AudioRenderer() = delete;

		static void init();
		static void terminate();
		static void submit(AudioBuffer* buffer);

		static void render();
		static void flush();

		static int fetchEmptySource();

		static bool hasFreeSlots();
	};



}