#pragma once
#include <string>


namespace archt {


	class AudioBuffer {

		std::string file;
		uint32_t id;

	public:
		AudioBuffer();
		AudioBuffer(const std::string& path);
		~AudioBuffer();

		inline uint32_t getId() const { return id; }

	};


}