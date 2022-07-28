#include "glmesh.h"

#include "../../filesystem/filemanager.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace archt {



	GLMesh::GLMesh() {}

	GLMesh::GLMesh(VBO* vbo, IBO* ibo) : vbo(vbo), ibo(ibo) {}

	GLMesh::GLMesh(VBO* vbo, IBO* ibo, const std::string& texture) : vbo(vbo), ibo(ibo) {

	}
	
	GLMesh::GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize) {
		vbo = new VBO(verteces, vSize);
		ibo = new IBO(indeces, iSize);
	}
	

	GLMesh::~GLMesh() {
		if (vbo) delete vbo;
		if (ibo) delete ibo;
	}

	void GLMesh::translate(const glm::vec3& t) {
		modelMatrix = glm::translate(modelMatrix, t);
	}

	void GLMesh::rotate(float angle, const glm::vec3& axis) {
		modelMatrix = glm::rotate(modelMatrix, angle, axis);

	}

	void GLMesh::scale(const glm::vec3& s) {
		modelMatrix = glm::scale(modelMatrix, s);
	}

	void GLMesh::resetMatrix() {
		modelMatrix = glm::mat4(1.0f);
	}


	void GLMesh::setVbo(VBO* vbo) {
		if (this->vbo) 
			delete this->vbo;

		this->vbo = vbo;
	}

	void GLMesh::setVbo(Vertex* verteces, uint32_t size) {
		if (vbo)
			delete vbo;

		vbo = new VBO(verteces, size);
	}

	void GLMesh::setIbo(IBO* ibo) {
		if (this->ibo)
			delete this->ibo;

		this->ibo = ibo;
	}

	void GLMesh::setIbo(uint32_t* indeces, uint32_t size) {
		if (ibo)
			delete ibo;

		ibo = new IBO(indeces, size);
	}

	void GLMesh::setTexture(GLTexture* tex) {
		if (this->tex)
			delete this->tex;

		this->tex = tex;
	}

	void GLMesh::setShader(GLShader* shader) {
		this->shader = shader;
	}

	void GLMesh::setModelMatrix(const glm::mat4& m) {
		modelMatrix = m;
	}

}