#include "rayequation.h"

namespace archt {


	glm::vec2 solveRayEquation(const glm::vec2& a1, const glm::vec2& b1, const glm::vec2& a2, const glm::vec2& b2) {

		glm::vec2 r = a1;
		glm::vec2 v = b1 - a1;

		glm::vec2 s = a2;
		glm::vec2 w = b2 - a2;

		float t = 0.0f;
		float u = 0.0f;

		u = ((v.x * s.y - v.x * r.y) + (v.y * r.x - v.y * s.x)) / (w.x * v.y - w.y * v.x);
		t = (s.x - r.x + u * w.x) / v.x;

		if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
			//__debugbreak();
		}

		return { t, u };
	}


}