#pragma once

#include "guiwindow.h"
#include <glm/vec2.hpp>
#include <vector>

#include "../opengl/glwindow.h"

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"


namespace archt {


	class Gui {

	public:
		static Gui* instance;

	private:

		std::vector<GuiWindow> constantWindows;
		static const int MAX_WINDOWS;
		static int index;
		GuiWindow* perFrameWindows = new GuiWindow[MAX_WINDOWS];

	public:
		Gui() = delete;
		Gui(glm::ivec2 windowSize);
		~Gui();

		void render();

		void submitWIndow(std::function<void()> renderFunc);
		void addGuiWindow(std::function<void()> renderFunc);



		static void init(GLWindow* window);
		static void terminate();
	};


}