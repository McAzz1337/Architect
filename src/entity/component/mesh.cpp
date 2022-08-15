#include "mesh.h"

#include "../../ptr.h"


namespace archt {

	Mesh::Mesh() {
		addComponent(make_ptr<Transform>());
	}

	Mesh::~Mesh() {}


	void Mesh::translate(const glm::vec3& t) {
		modelMatrix.translate(t);
	}

	void Mesh::rotate(float angle, const glm::vec3& axis) {
		modelMatrix.rotate(angle, axis);

	}

	void Mesh::scale(const glm::vec3& s) {
		modelMatrix.scale(s);
	}

	void Mesh::resetMatrix() {
		modelMatrix.reset();
	}

	void Mesh::setVBO(Vertex* verteces, uint32_t size) {
		if (!vbo)
			vbo = new VBO();
		vbo->setVerteces(verteces, size);
	}

	void Mesh::setIBO(uint32_t* indeces, uint32_t size) {
		if (!ibo)
			ibo = new IBO();
		ibo->setIndeces(indeces, size);
	}

}