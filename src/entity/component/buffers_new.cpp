#include "buffers_new.h"


#include <memory>

#include "../../gfx/opengl/glinclude.h"
#include "../../gfx/opengl/gldebug.h"
#include "../../gfx/vertex.h"

#define HAS_GPU_ALLOCATION id != 0

namespace archt {



	VBO_new::VBO_new() {}

	VBO_new::VBO_new(Vertex* verteces, uint32_t size) {
		data = new Vertex[size];
		memcpy_s(data, size * sizeof(Vertex), verteces, size * sizeof(Vertex));
		this->size = size;
	}

	VBO_new::~VBO_new() {
		if (data)
			delete[] data;

		if (HAS_GPU_ALLOCATION)
			deallocateOnGPU();
	}

	void VBO_new::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}


	void VBO_new::write(uint32_t offset, Vertex* d, uint32_t size) {
		if (!data) {
			data = new Vertex[size];
			memcpy_s(data, size * sizeof(Vertex), d, size * sizeof(Vertex));
			this->size = size;
		}
		else if (offset + size > this->size) {
			Vertex* newData = new Vertex[offset + size];
			memcpy_s(newData, this->size * sizeof(Vertex), data, this->size * sizeof(Vertex));
			memcpy_s(&newData[offset], size * sizeof(Vertex), d, size * sizeof(Vertex));
			delete[] data;
			data = newData;
			this->size = offset + size;
		}
		else {
			memcpy_s(data + offset, size * sizeof(Vertex), d, size * sizeof(Vertex));
		}
	}

	void VBO_new::upload(int offset, int length) const {

		if (length == 0)
			length = size;
		if (offset * sizeof(Vertex) + length * sizeof(Vertex) > bytes()) {
			__debugbreak();
		}
		CALL(glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(Vertex), length * sizeof(Vertex), data));
	}

	void VBO_new::allocateOnGPU(int size, int mode) {
		glGenBuffers(1, &id);
		bind();

		size = size < 0 ? bytes() : size * sizeof(Vertex);
		glBufferData(GL_ARRAY_BUFFER, size, data, mode);
	}

	void VBO_new::deallocateOnGPU() {
		glDeleteBuffers(1, &id);
		id = 0;
	}


	void VBO_new::print(int end) const {
		printf("VBO_new data:\n");
		for (int i = 0; i < end; i++) {
			data[i].print();
		}
		printf("-------------------\n");
	}

	glm::vec3* VBO_new::getPositionalCoordinates(int& out_size) const {
		out_size = size;
		glm::vec3* positions = new glm::vec3[size];
		for (int i = 0; i < size; i++) {
			positions[i] = data[i].pos;
		}
		return positions;
	}

	void VBO_new::setTexId(float id) {
		for (int i = 0; i < size; i++) {
			data[i].texId = id;
		}
	}

	void VBO_new::setMatrixId(float id) {
		for (int i = 0; i < size; i++) {
			data[i].matrixId = id;
		}
	}






	IBO_new::IBO_new() {}

	IBO_new::IBO_new(uint32_t* indeces, uint32_t size) {
		data = new uint32_t[size];
		memcpy_s(data, size * sizeof(uint32_t), indeces, size * sizeof(uint32_t));
		this->size = size;
	}

	IBO_new::~IBO_new() {
		if (data) {
			delete[] data;
		}

		if (HAS_GPU_ALLOCATION)
			deallocateOnGPU();
	}

	void IBO_new::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void IBO_new::write(uint32_t offset, uint32_t* d, uint32_t size, int vertexOffset) {
		if (!data) {
			data = new uint32_t[size];
			memcpy_s(data, size * sizeof(uint32_t), d, size * sizeof(uint32_t));
			this->size = size;
		}
		else if (offset + size > this->size) {
			uint32_t* newData = new uint32_t[offset + size];
			memcpy_s(newData, this->size * sizeof(uint32_t), data, this->size * sizeof(uint32_t));
			memcpy_s(&newData[offset], size * sizeof(uint32_t), d, size * sizeof(uint32_t));
			delete[] data;
			data = newData;
			this->size = offset + size;
		}
		else {
			memcpy_s(&data[offset], size * sizeof(uint32_t), d, size * sizeof(uint32_t));
		}

		if (vertexOffset > 0) {
			for (int i = offset; i < offset + size; i++) {
				data[i] += vertexOffset;
			}
		}
	}

	void IBO_new::upload(int offset, int length, int mode) const {
		if (length == 0)
			length = size;
		CALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), length * sizeof(uint32_t), data));
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes(), data, mode);
	}

	void IBO_new::allocateOnGPU(int size, int mode) {
		glGenBuffers(1, &id);
		bind();

		size = size < 0 ? bytes() : size * sizeof(uint32_t);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, mode);
	}

	void IBO_new::deallocateOnGPU() {
		glDeleteBuffers(1, &id);
		id = 0;
	}



	void IBO_new::print(int end) const {
		printf("IBO_new data:\n");
		for (int i = 0; i < end; i++) {
			printf("%i ", data[i]);
		}
		printf("\n---------------------\n");
	}





}