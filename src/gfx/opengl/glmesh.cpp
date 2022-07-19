#include "glmesh.h"

#include "../../filesystem/filemanager.h"

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
		FileManager::instance.deleteFile(tex->getFilePath(), FileManager::FileType::GL_TEXTURE_T);
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

}