#include "gui.h"



namespace archt {



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

	Gui::~Gui() {}

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
		
		setStyle();
	}

	void Gui::setStyle() {
	
		ImGuiStyle& style = ImGui::GetStyle();

		style.Colors[ImGuiCol_WindowBg] = ImColor(43, 45, 47);
		style.Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_Border] = ImColor(50, 50, 50);
		
		style.Colors[ImGuiCol_Tab] = ImColor(50, 50, 50);
		style.Colors[ImGuiCol_TabActive] = ImColor(121, 128, 134);
		style.Colors[ImGuiCol_TabUnfocused] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImColor(30, 30, 30);
		
		style.Colors[ImGuiCol_TitleBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(121, 128, 134);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(102, 97, 177);
		
		style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(60, 60, 60);
		

		style.Colors[ImGuiCol_SliderGrab] = ImColor(60, 60, 60);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(121, 128, 134);

		printf("styles\n");
	}

	void Gui::terminate() {
	
		if (instance) {
			delete instance;
			instance = nullptr;
		}

		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
	}

	void Gui::render() {
	
		if (docked)
			renderDocked();
		else
			renderUndocked();
	}

	//void Gui::submitWindowVoid(std::function<void()> renderFunc) {
	//	perFrameWindows.push_back(new GuiWindowVoid(renderFunc));
	//}
	//
	//GuiWindowBase* Gui::addGuiWindowVoid(std::function<void()> renderFunc) {
	//	constantWindows.push_back(new GuiWindowVoid(renderFunc));
	//	return constantWindows[constantWindows.size() - 1];
	//}

	void Gui::removeWindow(GuiWindow* window) {
		for (int i = 0; i < constantWindows.size(); i++) {
			if (constantWindows[i] == window) {
				constantWindows.erase(constantWindows.begin() + i);
				constantWindows.shrink_to_fit();
				break;
			}
		}
	}

	void Gui::setDockingMode(bool mode) {
		docked = mode;
	}

	void Gui::renderDocked() {
	

		ImGuiIO& io = ImGui::GetIO();
		(void) io;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool* p_open = new bool(true);
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else {
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		else {
			//ShowDockingDisabledMessage();
		}

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("Options")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Flag: NoSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
				if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
				if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
				if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
					*p_open = false;
				ImGui::EndMenu();
			}


			ImGui::EndMenuBar();

			for (GuiWindow* w : constantWindows)
				w->render();

			for (GuiWindow* w : perFrameWindows) {
				w->render();
			}
			perFrameWindows.erase(perFrameWindows.begin(), perFrameWindows.end());
			perFrameWindows.shrink_to_fit();

		}
		ImGui::End(); // ImGui::DockSpace();

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

	void Gui::renderUndocked() {
	
		ImGuiIO& io = ImGui::GetIO();
		(void) io;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (GuiWindow* w : constantWindows)
			w->render();

		for (GuiWindow* w : perFrameWindows) {
			w->render();
		}
		perFrameWindows.erase(perFrameWindows.begin(), perFrameWindows.end());
		perFrameWindows.shrink_to_fit();

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

}