#include "audiosource.h"

#include "AL/al.h"

namespace archt {


	AudioSource::AudioSource() {
		
		alGenSources(1, &id);

		alSourcef(id, AL_PITCH, pitch);
		alSourcef(id, AL_GAIN, gain);
		alSource3f(id, AL_POSITION, pos[0], pos[1], pos[2]);
		alSource3f(id, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		alSourcei(id, AL_LOOPING, loops);
		alSourcei(id, AL_BUFFER, 0);
	}
	

	AudioSource::AudioSource(AudioBuffer* buffer, float pitch, float gain, int loops) 
		: buffer(buffer), pitch(pitch), gain(gain), loops(loops) {
	
		alGenSources(1, &id);

		alSourcef(id, AL_PITCH, pitch);
		alSourcef(id, AL_GAIN, gain);
		alSource3f(id, AL_POSITION, pos[0], pos[1], pos[2]);
		alSource3f(id, AL_VELOCITY, velocity[0], velocity[1], velocity[2]);
		alSourcei(id, AL_LOOPING, loops);
		
		if (buffer)
			alSourcei(id, AL_BUFFER, buffer->getId());

	}
	
	AudioSource::~AudioSource() {
		if (id)
			alDeleteSources(1, &id);
	}


	void AudioSource::attachBuffer(AudioBuffer* buffer) const {
		if (this->buffer)
			detachBuffer();
		
		this->buffer = buffer;
		alSourcei(id, AL_BUFFER, buffer->getId());
	}

	void AudioSource::detachBuffer() const {
		alSourcei(id, AL_BUFFER, 0);
		this->buffer = nullptr;
	}

	void AudioSource::play() const {
		alSourcePlay(id);
	}
	
	void AudioSource::pause() const {
		alSourcePause(id);
	}
	
	void AudioSource::rewind() const {
		alSourceRewind(id);
	}
	
	void AudioSource::stop() const {
		alSourceStop(id);
	}

	bool AudioSource::isPlaying() const {
		if (!buffer) return false;
		int state;
		alGetSourcei(id, AL_SOURCE_STATE, &state);
		return state == AL_PLAYING;
	}



	void AudioSource::setPitch(float p) {
		pitch = p;
		alSourcef(id, AL_PITCH, pitch);
	}

	void AudioSource::setGain(float g) {
		gain = g;
		alSourcef(id, AL_GAIN, gain);
	}

	void AudioSource::setLoops(int l) {
		loops = l;
		alSourcei(id, AL_LOOPING, l);
	}

	void AudioSource::setPosition(const glm::vec3& pos) {
		this->pos[0] = pos[0];
		this->pos[1] = pos[1];
		this->pos[2] = pos[2];
		alSource3f(id, AL_POSITION, this->pos[0], this->pos[1], this->pos[2]);
	}

	void AudioSource::setVelocity(const glm::vec3& vel) {
		velocity[0] = vel[0];
		velocity[1] = vel[1];
		velocity[2] = vel[2];
		alSource3f(id, AL_POSITION, velocity[0], velocity[1], velocity[2]);
	}

	void AudioSource::addGain(float g) {
		
		gain += g;
		
		if (gain > 1.0f)
			gain = 1.0f;
		else if (gain < 0.0f)
			gain = 0.0f;

		alSourcef(id, AL_GAIN, gain);
	}

}