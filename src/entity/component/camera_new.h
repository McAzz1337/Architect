#pragma once

#if 1 
#include "../component.h"

#include "transform.h"

#include "../entity.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/transform.hpp>

namespace archt {

	class Camera_new : public Entity {

		Transform projection;
		mutable Transform view;

		glm::vec3 rotation = glm::vec3(0.0f);
		glm::vec3 position = glm::vec3(0.0f);

	public:
		Camera_new();
		Camera_new(float fov, float aspect, float near, float far);
		~Camera_new();



		void translate(const glm::vec3& t);
		void rotate(float angle, const glm::vec3& axis);

		void resetMatrix();
		void applyTransformation() const;

		void setPosition(glm::vec3 pos);
		void setRotation(glm::vec3 rot);


		inline const Transform& getProjection() const { return projection; }
		inline const Transform& getView() const { applyTransformation();  return view; }
		inline const Transform getProjectionView() const { applyTransformation(); return projection * view; }

		inline const Transform& getViewRaw() const { applyTransformation();  return view; }

		inline const glm::vec3 getPosition() const { return position; }
		inline const glm::vec3 getRotation() const { return rotation; }


	};
}
#endif