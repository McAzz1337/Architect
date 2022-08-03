#pragma once
#include "albuffer.h"
#include <string>

namespace archt {


	class AudioBuffer : public ALBuffer {

		std::string file;
		uint32_t id = 0;

	public:
		AudioBuffer();
		AudioBuffer(const std::string& path);
		~AudioBuffer();


		inline uint32_t getId() const { return id; }


	};


}