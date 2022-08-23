#include "camera_new.h"

#include "../../gfx/gui/gui.h"
#include "../../entity/component/mesh.h"

namespace archt {


	Camera_new::Camera_new() {

	}

	Camera_new::Camera_new(float fov, float aspect, float near, float far) {
		projection = Transform(glm::perspective(fov, aspect, near, far));
		view = Transform();

		translate({ 0.0f, 0.0f, -1.0f });


		auto lambda = [this]() {
			ImGui::Begin("Camera");

			applyTransformation();
			ImGui::Text("Matrix:");
			glm::mat4 m = view.getMatrix();

			for (int i = 0; i < 4; i++) {
				ImGui::Text("%f\t%f\t%f\t%f", m[i][0], m[i][1], m[i][2], m[i][3]);
			}
			ImGui::Text("Position:\t%f\t%f\t%f", m[3][0], m[3][1], m[3][2]);
			ImGui::Text("Pos:\t%f\t%f\t%f", position.x, position.y, position.z);


			ImGui::End();
		};
		//Gui::instance->addGuiWindow(lambda);

	}

	Camera_new::~Camera_new() {

	}

	void Camera_new::translate(const glm::vec3& t) {
		position += t;
	}

	void Camera_new::rotate(float angle, const glm::vec3& axis) {
		rotation += angle * axis;
	}

	void Camera_new::resetMatrix() {
		view.reset();
	}

	void Camera_new::applyTransformation() const {
		view.reset();

		view.rotate(rotation.x, { 1.0f, 0.0f, 0.0f });
		view.rotate(rotation.y, { 0.0f, 1.0f, 0.0f });
		view.rotate(rotation.z, { 0.0f, 0.0f, 1.0f });

		view.translate(position);


		ptr<Mesh> mesh =  getComponent<Mesh>();
		
		if (mesh) {
			mesh->resetMatrix();
			mesh->translate(position);
		}
	}

	

	void Camera_new::setPosition(glm::vec3 pos) {
		position = pos;
	}

	void Camera_new::setRotation(glm::vec3 rot) {
		rotation = rot;
	}



}
