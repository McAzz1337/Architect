#include "camera_new.h"


namespace archt {


	Camera_new::Camera_new() {

	}

	Camera_new::Camera_new(float fov, float aspect, float near, float far) {
		projection = Transform(glm::perspective(fov, aspect, near, far));
		view = Transform();

		translate({ 0.0f, 0.0f, -1.0f });
	}

	Camera_new::~Camera_new() {

	}

	void Camera_new::translate(const glm::vec3& t) {
		view.translate(t);
	}

	void Camera_new::rotate(float angle, const glm::vec3& axis) {
		view.rotate(angle, axis);
	}

	void Camera_new::resetMatrix() {
		view.reset();
	}



}
