#include "buffers.h"

#include <memory>

#include "glinclude.h"

namespace archt {



	VBO::VBO() {}

	VBO::VBO(Vertex* verteces, uint32_t size) : data(verteces), size(size) {

	}
	
	VBO::~VBO() {
		if (data)
			delete[] data;

		if (id != 0)
			glDeleteBuffers(1, &id);
	}

	void VBO::bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}


	void VBO::write(uint32_t offset, Vertex* d, uint32_t size) {
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

	void VBO::upload(int mode) const {
		bind();
		glBufferData(GL_ARRAY_BUFFER, bytes(), data, mode);
	}

	void VBO::allocateOnGPU() {
		glGenBuffers(1, &id);
	}

	void VBO::print(int end) const {
		printf("VBO data:\n");
		for (int i = 0; i < end; i++) {
			data[i].print();
		}
		printf("-------------------\n");
	}

	void VBO::setTexId(float id) {
		for (int i = 0; i < size; i++) {
			data[i].texId = id;
		}
	}






	IBO::IBO() {}

	IBO::IBO(uint32_t* indeces, uint32_t size) : data(indeces), size(size) {

	}

	IBO::~IBO() {
		if (data) {
			delete[] data;
		}

		if (id != 0)
			glDeleteBuffers(1, &id);
	}

	void IBO::bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void IBO::write(uint32_t offset, uint32_t* d, uint32_t size) {
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
	}

	void IBO::upload(int mode) const {
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes(), data, mode);
	}

	void IBO::allocateOnGPU() {
		glGenBuffers(1, &id);
	}



	void IBO::print() const {
		printf("IBO data:\n");
		for (int i = 0; i < size; i++) {
			printf("%i,", data[i]);
		}
	}





}