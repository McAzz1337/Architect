#include "vertex.h"
#include <iostream>

namespace archt {
	
	
	Vertex::Vertex() {}

	Vertex::Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv, float texId)
		: pos(pos), normal(normal), uv(uv), texId(texId) {

	}

	Vertex::~Vertex() {}

	void Vertex::print() const {
		printf("pos:%f %f %f\t normal:%f %f %f\t uv:%f %f \t texId:%f\n");
	}

}