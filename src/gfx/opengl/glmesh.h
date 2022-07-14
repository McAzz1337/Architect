#pragma once

#include "buffers.h"

namespace archt {


	class GLMesh {

		VBO* vbo = nullptr;
		IBO* ibo = nullptr;


	public:
		GLMesh();
		GLMesh(VBO* vbo, IBO* ibo);
		GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize);
		~GLMesh();

		void setVbo(VBO* vbo);
		void setVbo(Vertex* verteces, uint32_t size);

		void setIbo(IBO* ibo);
		void setIbo(uint32_t* indeces, uint32_t size);


		inline VBO* getVBO() const { return vbo; }
		inline IBO* getIBO() const { return ibo; }

	};


}