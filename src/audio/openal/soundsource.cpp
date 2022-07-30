#include "soundsource.h"

#include "AL/al.h"

namespace archt {


	SoundSource::SoundSource() {
		
		alGenSources(1, &id);

		alSourcef(id, AL_PITCH, pitch);
		alSourcef(id, AL_GAIN, gain);
		alSource3f(id, AL_POSITION, pos[0], pos[1], pos[2]);
		alSource3f(id, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		alSourcei(id, AL_LOOPING, loop);
		alSourcei(id, AL_BUFFER, 0);
	}
	
	SoundSource::SoundSource(AudioBuffer* buffer) : buffer(buffer) {
		
		alGenSources(1, &id);
		
		alSourcef(id, AL_PITCH, pitch);
		alSourcef(id, AL_GAIN, gain);
		alSource3f(id, AL_POSITION, pos[0], pos[1], pos[2]);
		alSource3f(id, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		alSourcei(id, AL_LOOPING, loop);
		alSourcei(id, AL_BUFFER, buffer->getId());

	}
	
	SoundSource::~SoundSource() {
		if (id)
			alDeleteSources(1, &id);
	}


	void SoundSource::attachBuffer(AudioBuffer* buffer) const {
		if (this->buffer)
			detachBuffer();
		
		this->buffer = buffer;
		alSourcei(id, AL_BUFFER, buffer->getId());
	}

	void SoundSource::detachBuffer() const {
		alSourcei(id, AL_BUFFER, 0);
		this->buffer = nullptr;
	}

	void SoundSource::play() const {
		alSourcePlay(id);
	}
	
	void SoundSource::pause() const {
		alSourcePause(id);
	}
	
	void SoundSource::rewind() const {
		alSourceRewind(id);
	}
	
	void SoundSource::stop() const {
		alSourceStop(id);
	}

	bool SoundSource::isPlaying() const {
		if (!buffer) return false;
		int state;
		alGetSourcei(id, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}

}