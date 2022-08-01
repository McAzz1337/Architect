/*#include "musicbuffer.h"
#include <AL/al.h>

#include "aldebug.h"

namespace archt {


	MusicBuffer::MusicBuffer() {

	}

	MusicBuffer::MusicBuffer(const std::string& path) : path(path) {

		file = sf_open(path.c_str(), SFM_READ, &info);

		if (!file) {
			printf("Failed to open sound file: %s\n", path.c_str());
			__debugbreak();
		}
		else if (info.frames < 1 || info.frames >(sf_count_t) (INT_MAX / sizeof(short)) / info.channels) {
			printf("Bad sample count in %s\n", path.c_str());
			__debugbreak();
		}
		sf_count_t frameCount = 0;




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
	
		if (!format) {
			__debugbreak();
		}

		bytes = (ALsizei) (samples * info.channels) * (ALsizei) (sizeof(int16_t));

		buffer = static_cast<int16_t*>(malloc(bytes));

		AL_CALL(alGenBuffers(MAX_MUSIC_BUFFERS, id));

	}

	MusicBuffer::~MusicBuffer() {

		AL_CALL(alDeleteBuffers(MAX_MUSIC_BUFFERS, id));

		if (file)
			sf_close(file);

		file = nullptr;

		free(buffer);

	}

	int MusicBuffer::attachToSource() {

		bufferCount = 0;
		for (; bufferCount < MAX_MUSIC_BUFFERS; bufferCount++) {

			sf_count_t size = sf_read_short(file, buffer, samples);

			if (size < 1)
				break;

			size *= info.channels * (sf_count_t) sizeof(int16_t);
			AL_CALL(alBufferData(id[bufferCount], format, buffer, size, info.samplerate));
		}
		
		printf("buffers attached %i\n", bufferCount);

		return bufferCount;
	}

	int MusicBuffer::updateBufferStream(uint32_t srcId) {


		int processed = 0;
		AL_CALL(alGetSourcei(srcId, AL_BUFFERS_PROCESSED, &processed));
	
		if (processed > 0) 
			printf("buffers processed %i\n", processed);
		
		while (processed > 0) {

			uint32_t bId;
			sf_count_t size;

			AL_CALL(alSourceUnqueueBuffers(srcId, 1, &bId));
			processed--;

			size = sf_read_short(file, buffer, samples);
			if (size > 0) {
				size *= info.channels * (sf_count_t) sizeof(int16_t);
				AL_CALL(alBufferData(bId, format, buffer, size, info.samplerate));
				alSourceQueueBuffers(srcId, 1, &bId);
			}
		}


		int queued = 0;
		AL_CALL(alGetSourcei(srcId, AL_BUFFERS_QUEUED, &queued));

		return queued;
	}

}
*/