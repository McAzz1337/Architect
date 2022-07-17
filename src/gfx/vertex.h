#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>



namespace archt {

	struct Vertex {
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 uv;
		uint32_t texId = 0;

		Vertex();
		Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& uv, uint32_t texId);
		~Vertex();

	};
}