#include "entity_s.h"

#include "../gfx/gui/gui.h"



namespace archt {



	Entity_s::Entity_s() {
	
		/*
		auto lambda = [this]() {
			ImGui::Begin("Entity_s");
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

	Entity_s::Entity_s(entt::entity id) : id(id) {}

	Entity_s::~Entity_s() {}




}