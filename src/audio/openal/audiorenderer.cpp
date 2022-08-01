#include "audiorenderer.h"

#include "../../chronos/deltatime.h"

#include <chrono>
#include <thread>
#include <typeindex>


#define PLAY

namespace archt {


	const int AudioRenderer::MAX_SOUND_SOURCES = 10;
	const int AudioRenderer::MAX_BUFFERS = 100;

	int AudioRenderer::currentInsert = 0;
	int AudioRenderer::currentBuffer = 0;

	double AudioRenderer::fadeDuration = 0.0;
	bool AudioRenderer::transition = false;

	ALListener* AudioRenderer::listener = nullptr;

	AudioSource* AudioRenderer::backgroundMusic = nullptr;
	AudioSource* AudioRenderer::nextBackgroundMusic = nullptr;
	AudioSource** AudioRenderer::soundSources = nullptr;
	std::vector <AudioBuffer*> AudioRenderer::bufferQueue;

	Thread<void> AudioRenderer::thread;

	void AudioRenderer::init() {

		soundSources = new AudioSource*[MAX_SOUND_SOURCES];
		for (int i = 0; i < MAX_SOUND_SOURCES; i++) {
			soundSources[i] = new AudioSource();
		}
		backgroundMusic = new AudioSource();
		backgroundMusic->setLoops(1);
		nextBackgroundMusic = new AudioSource();
		nextBackgroundMusic->setGain(0.0f);
		nextBackgroundMusic->setLoops(1);

		listener = new ALListener();
	}

	void AudioRenderer::terminate() {
		delete backgroundMusic;
		delete nextBackgroundMusic;

		for (int i = 0; i < MAX_SOUND_SOURCES; i++) {
			delete soundSources[i];
		}
		delete[] soundSources;
	}

	void AudioRenderer::submit(AudioBuffer* buffer) {
		if (bufferQueue.size() >= MAX_BUFFERS) {
			__debugbreak();
		}

		bufferQueue.insert(bufferQueue.begin(), 1, buffer);
	}

	void AudioRenderer::render() {

#ifdef PLAY
		while (bufferQueue.size() > 0) {
		
			int source = fetchEmptySource();
			if (source == MAX_SOUND_SOURCES)
				break;

			int size = bufferQueue.size();
			soundSources[source]->attachBuffer(bufferQueue.at(size - 1));
			bufferQueue.pop_back();
			bufferQueue.shrink_to_fit();
			
			soundSources[source]->play();
		}

	
		if (fadeDuration > 0.0) {
			
			double elapsed = DeltaTime::instance.getSeconds();
			float fadeStep = ((float) (elapsed / fadeDuration));
			
			backgroundMusic->addGain(-fadeStep);
			
			if (transition) {
				if (!nextBackgroundMusic->isPlaying())
					nextBackgroundMusic->play();

				nextBackgroundMusic->addGain(fadeStep);

				if (nextBackgroundMusic->getGain() == 1.0f) {
					backgroundMusic->stop();
					AudioSource* temp = backgroundMusic;
					backgroundMusic = nextBackgroundMusic;
					nextBackgroundMusic = temp;

					transition = false;
					fadeDuration = 0.0;
				}
			}
			else if (backgroundMusic->getGain() >= 0.0f) {
				fadeDuration = 0.0;
			}
		}

		if (thread.isDone()) {
			thread.result();
		}
#endif

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
		return bufferQueue.size() < MAX_BUFFERS;
	}

	void AudioRenderer::setBackgroundMusic(AudioBuffer* buffer) {
		
		if (backgroundMusic->isPlaying())
			backgroundMusic->stop();

		backgroundMusic->attachBuffer(buffer);
	}
	
	void AudioRenderer::playBackgroundMusic() {
#ifdef PLAY
		if (backgroundMusic->isPlaying())
			return;
		backgroundMusic->play();
#endif
	}
	
	void AudioRenderer::pauseBackgroundMusic() {
		if (!backgroundMusic->isPlaying())
			return;

		backgroundMusic->pause();
	}
	
	void AudioRenderer::stopBackgroundMusic() {
		
		if (!backgroundMusic->isPlaying())
			return;
		
		backgroundMusic->stop();
	}
	
	void AudioRenderer::fadeBackgroundMusic(bool transition, double fadeDuration, AudioBuffer* next) {
		
		AudioRenderer::transition = transition;
		AudioRenderer::fadeDuration = fadeDuration;
		nextBackgroundMusic->attachBuffer(next);
	}

	void AudioRenderer::swapBackgroundMusic(AudioBuffer* buffer, bool stopImmediately, double delay) {
		
		if (stopImmediately)
			stopBackgroundMusic();

		
		auto func = [buffer, &stopImmediately, &delay]() {
			
			std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(delay * 1000));
			if (!stopImmediately)
				stopBackgroundMusic();
			
			setBackgroundMusic(buffer);
			playBackgroundMusic();
		};
		std::function<void(void)> f = func;
		thread.setFunction(func);
		thread.start();
	}

	

}