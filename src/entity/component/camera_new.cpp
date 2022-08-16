#include "camera_new.h"

#include "../../gfx/gui/gui.h"
namespace archt {


	Camera_new::Camera_new() {

	}

	Camera_new::Camera_new(float fov, float aspect, float near, float far) {
		projection = Transform(glm::perspective(fov, aspect, near, far));
		view = Transform();

		translate({ 0.0f, 0.0f, 0.3f });


		auto lambda = [this]() {
			ImGui::Begin("Camera");

			ImGui::Text("Matrix:");
			glm::mat4 m = view.getMatrix();

			for (int i = 0; i < 4; i++) {
				ImGui::Text("%f\t%f\t%f\t%f", m[i][0], m[i][1], m[i][2], m[i][3]);
			}

			ImGui::End();
		};
		Gui::instance->addGuiWindow(lambda);

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
