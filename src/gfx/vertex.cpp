#include "vertex.h"


namespace archt {
	
	
	Vertex::Vertex() {}

	Vertex::Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv) 
		: pos(pos), normal(normal), uv(uv) {

	}

	Vertex::~Vertex() {}
}