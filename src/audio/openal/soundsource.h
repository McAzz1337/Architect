#pragma once
#include "audiobuffer.h"


namespace archt {


	class SoundSource {

		uint32_t id = 0;
		float pitch = 1.0f;
		float gain = 1.0f;
		float pos[3] = { 0.0f, 0.0f, 0.0f};
		float velocity[3] = { 0.0f, 0.0f, 0.0f };
		bool loop = false;
		mutable AudioBuffer* buffer = nullptr;

	public:
		SoundSource();
		SoundSource(AudioBuffer* buffer);
		~SoundSource();


		void attachBuffer(AudioBuffer* buffer) const;
		void detachBuffer() const;

		void play() const;
		void pause() const;
		void rewind() const;
		void stop() const;

		bool isPlaying() const;

	};


}