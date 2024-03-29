#include "gui.h"

#include <functional>
#include "../../vendor/imgui/imconfig.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"



namespace archt{


	Gui* Gui::instance = nullptr;


	Gui::Gui(glm::ivec2 windowSize) {
		ImGuiIO& io = ImGui::GetIO();
		(void) io;
		io.DisplaySize.x = windowSize.x;
		io.DisplaySize.y = windowSize.y;

		

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}

	Gui::~Gui() {
	
	}

	void Gui::render() {

		ImGuiIO& io = ImGui::GetIO();
		(void) io;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (GuiWindow& w : windows)
			w.render();


		ImGui::Render();

		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable
			&& io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

			GLFWwindow* window = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(window);
		}
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Gui::addGuiWindow(std::function<void()> renderFunc) {
		windows.push_back(GuiWindow(renderFunc));
	}

	void Gui::init(GLWindow* window) {
		if (instance)
			return;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		(void) io; 
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui_ImplOpenGL3_Init("#version 450 core");
		ImGui_ImplGlfw_InitForOpenGL(window->getHandle(), true);
		ImGui::StyleColorsDark();
		glm::ivec2 windowSize = window->getSize();
		instance = new Gui(windowSize);
	}

	void Gui::terminate() {
		if (instance) {
			delete instance;
			instance = nullptr;
		}

		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
	}


	

}