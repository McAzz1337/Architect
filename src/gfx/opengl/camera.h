#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>


namespace archt {


	class Camera {

		glm::mat4 projection;
		glm::mat4 view;

	public:
		Camera();
		Camera(float fov, float aspect, float near, float far);
		~Camera();

		void translate(const glm::vec3& t);
		void rotate(const glm::vec3& axis, float angle);

		inline const glm::mat4& getProjection() const { return projection; }
		inline const glm::mat4& getView() const { return view; }
		inline const glm::mat4& getProjectionView() const { return projection * view; }


	};



}