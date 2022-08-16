#include "entity.h"

#include "../gfx/gui/gui.h"

#include "component/mesh.h"
#include "component/transform.h"

namespace archt {



	Entity::Entity() {
	
		/*
		auto lambda = [this]() {
			ImGui::Begin("Entity");
			ImGui::Text("Matrix:");
			glm::mat4 m = getComponent<Mesh>()->getTransform()->getMatrix();
		
			for (int i = 0; i < 4; i++) {
				ImGui::Text("%f\t%f\t%f\t%f", m[i][0], m[i][1], m[i][2], m[i][3]);
			}
		
			ImGui::End();
		};
		Gui::instance->addGuiWindow(lambda);
		*/
	}

	Entity::~Entity() {}

}