#pragma once
#include "../vertex.h"
#include <typeindex>

namespace archt {

	class VBO {

		uint32_t id = 0;
		Vertex* data = nullptr;
		uint32_t size = 0;

	public:
		VBO();
		VBO(Vertex* verteces, uint32_t size);
		~VBO();

		void allocateOnGPU();
		void bind() const;
		void write(uint32_t offset, Vertex* d, uint32_t size);
		void upload(int mode) const;

		void setTexId(float id);

		void print(int end) const;

		inline Vertex* getData() const { return data; }
		inline int getSize() const { return size; }
		inline int bytes() const { return size * sizeof(Vertex); }
	};



	class IBO {

		uint32_t id = 0;
		uint32_t* data = nullptr;
		uint32_t size = 0;

	public:
		IBO();
		IBO(uint32_t* indeces, uint32_t size);
		~IBO();


		void allocateOnGPU();
		void bind() const;
		void write(uint32_t offset, uint32_t* d, uint32_t size, int vertexOffset);
		void upload(int mode) const;

		void print(int end) const;


		inline uint32_t* getData() const { return data; }
		inline int getSize() const { return size; }
		inline int bytes() const { return size * sizeof(uint32_t); }
	};





}