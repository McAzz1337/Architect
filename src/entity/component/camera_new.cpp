#if 1
#include "camera_new.h"


namespace archt {


	Camera_new::Camera_new() {

	}

	Camera_new::Camera_new(float fov, float aspect, float near, float far) {
		projection = glm::perspective(fov, aspect, near, far);
		view = glm::mat4(1.0f);

		translate({ 0.0f, 0.0f, 1.0f });
	}

	Camera_new::~Camera_new() {

	}

	void Camera_new::translate(const glm::vec3& t) {
		view = glm::translate(view, t);
	}

	void Camera_new::rotate(const glm::vec3& axis, float angle) {
		view = glm::rotate(view, angle, axis);
	}

	void Camera_new::resetMatrix() {
		view = glm::mat4(1.0f);
		translate({ 0.0f, 0.0f, 1.0f });
	}



}
#endif