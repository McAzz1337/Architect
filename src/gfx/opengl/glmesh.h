#pragma once

#include "buffers.h"
#include "gltexture.h"

#include <string>

namespace archt {


	class GLMesh {

		VBO* vbo = nullptr;
		IBO* ibo = nullptr;
		GLTexture* tex = nullptr;

	public:
		GLMesh();
		GLMesh(VBO* vbo, IBO* ibo);
		GLMesh(VBO* vbo, IBO* ibo, const std::string& texture);
		GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize);
		~GLMesh();

		void setVbo(VBO* vbo);
		void setVbo(Vertex* verteces, uint32_t size);

		void setIbo(IBO* ibo);
		void setIbo(uint32_t* indeces, uint32_t size);
		void setTexture(GLTexture* tex);


		inline VBO* getVBO() const { return vbo; }
		inline IBO* getIBO() const { return ibo; }
		inline GLTexture* getTexture() const { return tex; }

	};


}