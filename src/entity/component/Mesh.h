#pragma once

#include "../component.h"

#include "camera_new.h"

#include "transform.h"

#include "../../gfx/opengl/buffers.h"

#include <glm/vec2.hpp>

namespace archt {

	class Mesh : public Component {

		VBO* vbo = nullptr;
		IBO* ibo = nullptr;
		Transform modelMatrix;

	public:
		Mesh();
		~Mesh();

		void translate(const glm::vec3& t);
		void rotate(float angle, const glm::vec3& axis);
		void scale(const glm::vec3& s);

		void resetMatrix();

		bool checkCollision(const Mesh& other, const Camera_new& cam) const;

		glm::vec2* getPositionsTranslated(const Camera_new& cam, int& out_size) const;


		void createGuiWindow(ptr<Camera_new> cam);

		void setVBO(Vertex* verteces, uint32_t size);
		void setIBO(uint32_t* indeces, uint32_t size);

		inline VBO* getVBO() { return vbo; }
		inline IBO* getIBO() { return ibo; }
		 
		inline const Transform& getTransform() const { return modelMatrix; }

	};


}