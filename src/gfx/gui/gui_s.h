#pragma once

#include "guiwindow_s.h"
#include "../opengl/glwindow.h"

#include "../../vendor/imgui/imconfig.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "../../vendor/imgui/imgui.h"


namespace archt {

	class Gui_s {
	
	public:
		static Gui_s* instance;

	private:

		std::vector<BaseWindow*> constantWindows;
		std::vector<BaseWindow*> perFrameWindows;



		bool docked = true;

		Gui_s(glm::ivec2 windowSize);
		~Gui_s();
	public:

		static void init(GLWindow* window);
		static void terminate();

		void render();

		void submitWindow(std::function<void()> renderFunc);
		BaseWindow* addGuiWindow(std::function<void()> renderFunc);


		template <typename F, typename... Args>
		void submitWindow_s(F&& f, Args&&... args) {
			perFrameWindows.push_back(createGuiWindow(f, std::forward<Args>(args)...));
		}

		template <typename F, typename... Args>
		BaseWindow* addGuiWindow_s(F&& f, Args&&... args) {
			constantWindows.push_back(createGuiWindow(f, std::forward<Args>(args)...));
			return constantWindows[constantWindows.size() - 1];
		}

		void removeWindow(BaseWindow* window);

		void setDockingMode(bool mode);

		

	private:
		void renderDocked();
		void renderUndocked();


	};


}