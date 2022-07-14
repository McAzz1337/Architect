#include "glmesh.h"


namespace archt {



	GLMesh::GLMesh() {}

	GLMesh::GLMesh(VBO* vbo, IBO* ibo) : vbo(vbo), ibo(ibo) {}

	GLMesh::GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize) {
		vbo = new VBO(verteces, vSize);
		ibo = new IBO(indeces, iSize);

	}
	
	GLMesh::~GLMesh() {
		if (vbo) delete vbo;
		if (ibo) delete ibo;
	}

	void GLMesh::setVbo(VBO* vbo) {
		if (vbo) 
			delete vbo;

		this->vbo = vbo;
	}

	void GLMesh::setVbo(Vertex* verteces, uint32_t size) {
		if (vbo)
			delete vbo;

		vbo = new VBO(verteces, size);
	}

	void GLMesh::setIbo(IBO* ibo) {
		if (ibo)
			delete ibo;

		this->ibo = ibo;
	}

	void GLMesh::setIbo(uint32_t* indeces, uint32_t size) {
		if (ibo)
			delete ibo;

		ibo = new IBO(indeces, size);
	}

}