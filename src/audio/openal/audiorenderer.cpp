#include "audiorenderer.h"



namespace archt {


	const int AudioRenderer::MAX_SOUND_SOURCES = 10;
	const int AudioRenderer::MAX_BUFFERS = 100;

	int AudioRenderer::currentInsert = 0;
	int AudioRenderer::currentBuffer = 0;


	SoundSource** AudioRenderer::soundSources = nullptr;
	std::vector <AudioBuffer*> AudioRenderer::bufferQueue;

	void AudioRenderer::init() {
		soundSources = new SoundSource*[MAX_SOUND_SOURCES];
		for (int i = 0; i < MAX_SOUND_SOURCES; i++) {
			soundSources[i] = new SoundSource();
		}
		bufferQueue.reserve(MAX_BUFFERS);
	}

	void AudioRenderer::terminate() {

	}

	void AudioRenderer::submit(AudioBuffer* buffer) {
		if (bufferQueue.size() >= MAX_BUFFERS) {
			__debugbreak();
		}

		bufferQueue.insert(bufferQueue.begin(), 1, buffer);
	}

	void AudioRenderer::render() {

		while (bufferQueue.size() > 0) {
		
			int source = fetchEmptySource();
			if (source == MAX_SOUND_SOURCES)
				break;

			int size = bufferQueue.size();
			soundSources[source]->attachBuffer(bufferQueue.at(size - 1));
			bufferQueue.pop_back();
			bufferQueue.resize(size - 1);
			
			soundSources[source]->play();
		}
	}

	void AudioRenderer::flush() {
		for (int i = 0; i < MAX_SOUND_SOURCES; i++) {

			if (soundSources[i]->isPlaying())
				soundSources[i]->stop();

			soundSources[i]->detachBuffer();
		}
		for (int i = 0; i < MAX_BUFFERS; i++) {
			bufferQueue[i] = nullptr;
		}
		currentInsert = 0;
		currentBuffer = 0;
	}

	int AudioRenderer::fetchEmptySource() {

		int i = 0;
		for (; i < MAX_SOUND_SOURCES; i++) {
			if (!(soundSources[i]->isPlaying()))
				break;
		}

		return i;
	}


	bool AudioRenderer::hasFreeSlots() {
		return bufferQueue.size() != MAX_BUFFERS;
	}

}