#pragma once

#include "buffers.h"
#include "gltexture.h"
#include "glshader.h"

#include <glm/mat4x4.hpp>
#include <string>

namespace archt {


	class GLMesh {

		VBO* vbo = nullptr;
		IBO* ibo = nullptr;
		GLTexture* tex = nullptr;
		glm::mat4 modelMatrix;
		GLShader* shader = nullptr;

	public:
		GLMesh();
		GLMesh(VBO* vbo, IBO* ibo);
		GLMesh(VBO* vbo, IBO* ibo, const std::string& texture);
		GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize);
		~GLMesh();

		void translate(const glm::vec3 t);
		void rotate(float angle, const glm::vec3 axis);
		void scale(const glm::vec3 s);


		void setVbo(VBO* vbo);
		void setVbo(Vertex* verteces, uint32_t size);

		void setIbo(IBO* ibo);
		void setIbo(uint32_t* indeces, uint32_t size);
		void setTexture(GLTexture* tex);
		void setShader(GLShader* shader);
		void setModelMatrix(const glm::mat4& m);

		inline VBO* getVBO() const { return vbo; }
		inline IBO* getIBO() const { return ibo; }
		inline GLTexture* getTexture() const { return tex; }
		inline GLShader* getShader() const { return shader; }
		inline const glm::mat4& getModelMatrix() const { return modelMatrix; }

	};


}