#pragma once

#include "audiobuffer.h"
#include "audiosource.h"


#include <vector>
#include <future>

#include "../../thread/thread.h"

namespace archt {

	class AudioRenderer {

		static const int MAX_SOUND_SOURCES;
		static const int MAX_BUFFERS;

		static int currentInsert;
		static int currentBuffer;

		static double fadeDuration;
		static bool transition;

		static AudioSource* backgroundMusic;
		static AudioSource* nextBackgroundMusic;
		static AudioSource** soundSources;
		static std::vector<AudioBuffer*> bufferQueue;
		static Thread<void> thread;


	public:
		AudioRenderer() = delete;

		static void init();
		static void terminate();
		static void submit(AudioBuffer* buffer);

		static void render();
		static void flush();

		static int fetchEmptySource();

		static bool hasFreeSlots();

		static void setBackgroundMusic(AudioBuffer* buffer);
		static void playBackgroundMusic();
		static void pauseBackgroundMusic();
		static void stopBackgroundMusic();
		static void fadeBackgroundMusic(bool transition, double fadeDuration = 0.0, AudioBuffer* next = nullptr);
		static void swapBackgroundMusic(AudioBuffer* buffer, bool stopImmediately, double delay = 0.0);

	};



}