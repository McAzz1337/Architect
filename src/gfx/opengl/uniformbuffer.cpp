#include "uniformbuffer.h"

#include "glinclude.h"

namespace archt {
	
	Uniformbuffer::Uniformbuffer() {
	}

	Uniformbuffer::Uniformbuffer(void* data, uint32_t size, uint32_t binding) : data(data), size(size), binding(binding) {
	
		glGenBuffers(1, &id);
		glBindBuffer(GL_UNIFORM_BUFFER, id);
		glBufferData(GL_UNIFORM_BUFFER, size * sizeof(float), data, GL_DYNAMIC_DRAW);

		glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, id, 0, size);
	}
	
	Uniformbuffer::~Uniformbuffer() {
		if (data)
			delete[] data;
	}

	void Uniformbuffer::write(uint32_t offset, void* d, uint32_t size) {
		
		if (!data) {
			data = d;
			this->size = size;
		}
		else if (offset + size > this->size) {
			void* newData = malloc((offset + size) * sizeof(float));
			memcpy_s(newData, offset, data, offset);
			memcpy_s(&((float*) newData)[offset], size, d, size );
			delete[] data;
			data = newData;
			this->size = offset + size;
		}
		else {
			memcpy_s(&((float*) data)[offset], size, d, size);
		}
	}

	void Uniformbuffer::upload() const {
		glBufferSubData(GL_UNIFORM_BUFFER, 0, size, data);
	}


	int Uniformbuffer::getUniformBlockLocation(uint32_t shaderId, const std::string& blockName) const {
		return glGetUniformBlockIndex(shaderId, blockName.c_str());
	}


	void Uniformbuffer::bind() const {
		glBindBuffer(GL_UNIFORM_BUFFER, id);
	}


	void Uniformbuffer::bindUniformBlock(uint32_t shaderId, const std::string& blockName) const {
		int location = getUniformBlockLocation(shaderId, blockName);
		if (location == -1)
			__debugbreak();
		glUniformBlockBinding(shaderId, location, binding);
	}

}