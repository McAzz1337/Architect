#include "glvertexarray.h"

#include "glinclude.h"

namespace archt {

	

	GLVertexarray::GLVertexarray() {

	}

	GLVertexarray::GLVertexarray(VBO* vbo, IBO* ibo) {

		glGenVertexArrays(1, &id);
		glBindVertexArray(id);

		vbo->bind();
		ibo->bind();


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, pos));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, normal));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, uv));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, texId));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*) offsetof(Vertex, matrixId));
	}

	GLVertexarray::~GLVertexarray() {
		glDeleteVertexArrays(1, &id);
	}

	void GLVertexarray::bind() const {
		glBindVertexArray(id);
	}



}