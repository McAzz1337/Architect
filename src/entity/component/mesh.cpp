#include "mesh.h"

#include "../../ptr.h"

#include "../../gfx/gui/gui.h"

namespace archt {

	Mesh::Mesh() {
		//addComponent(make_ptr<Transform>());
		modelMatrix = Transform();
	}

	Mesh::~Mesh() {}


	void Mesh::translate(const glm::vec3& t) {
		modelMatrix.translate(t);
	}

	void Mesh::rotate(float angle, const glm::vec3& axis) {
		modelMatrix.rotate(angle, axis);

	}

	void Mesh::scale(const glm::vec3& s) {
		modelMatrix.scale(s);
	}

	void Mesh::resetMatrix() {
		modelMatrix.reset();
	}

	void Mesh::createGuiWindow(ptr<Camera_new> cam) {
		
		auto lambda = [this, &cam] {
			glm::mat4 m = (cam->getProjectionView() * modelMatrix).getMatrix();

			ImGui::Begin("Mesh");
			ImGui::Text("Matrix:");

			for (int i = 0; i < 4; i++) {
				ImGui::Text("%f\t%f\t%f\t%f", m[i][0], m[i][1], m[i][2], m[i][3]);
			}

			ImGui::End();
		};
		Gui::instance->addGuiWindow(lambda);
	}

	void Mesh::setVBO(Vertex* verteces, uint32_t size) {
		if (!vbo)
			vbo = new VBO();
		vbo->setVerteces(verteces, size);
	}

	void Mesh::setIBO(uint32_t* indeces, uint32_t size) {
		if (!ibo)
			ibo = new IBO();
		ibo->setIndeces(indeces, size);
	}

}