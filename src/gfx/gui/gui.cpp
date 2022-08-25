#include "gui.h"



namespace archt {



	Gui* Gui::instance = nullptr;

	const std::string Gui::styleFile = "vendor/imgui/style.txt";


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
		createStyleWindow();
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

		style.Colors[ImGuiCol_WindowBg] = ImColor(50, 50, 50);
		style.Colors[ImGuiCol_ChildBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_Border] = ImColor(50, 50, 50);
		
		style.Colors[ImGuiCol_Tab] = ImColor(50, 50, 50);
		style.Colors[ImGuiCol_TabHovered] = ImColor(100, 100, 100);
		style.Colors[ImGuiCol_TabActive] = ImColor(100, 100, 100);
		style.Colors[ImGuiCol_TabUnfocused] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImColor(30, 30, 30);
		
		style.Colors[ImGuiCol_TitleBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(100, 100, 100);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(102, 97, 177);
		
		style.Colors[ImGuiCol_FrameBg] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(60, 60, 60);
		

		style.Colors[ImGuiCol_SliderGrab] = ImColor(60, 60, 60);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(121, 128, 134);

		style.Colors[ImGuiCol_ResizeGrip] = ImColor(30, 30, 30);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImColor(100, 100, 100);
		style.Colors[ImGuiCol_ResizeGripActive] = ImColor(100, 100, 100);

		style.Colors[ImGuiCol_DockingPreview] = ImColor(100, 100, 100);
		style.Colors[ImGuiCol_DockingEmptyBg] = ImColor(255, 255, 255);


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

	void Gui::createStyleWindow() {
	
		auto lambda = [this]() {
			
			ImGuiStyle& style = ImGui::GetStyle();
			ImGui::Begin("Style");

			ImGui::SliderFloat4("Border", &style.Colors[ImGuiCol_Border].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Text", &style.Colors[ImGuiCol_Text].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TextDisabled", &style.Colors[ImGuiCol_TextDisabled].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("WindowBg", &style.Colors[ImGuiCol_WindowBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ChildBg", &style.Colors[ImGuiCol_ChildBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("PopupBg", &style.Colors[ImGuiCol_PopupBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Border", &style.Colors[ImGuiCol_Border].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("BorderShadow", &style.Colors[ImGuiCol_BorderShadow].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("FrameBg", &style.Colors[ImGuiCol_FrameBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("FrameBgHovered", &style.Colors[ImGuiCol_FrameBgHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("FrameBgActive", &style.Colors[ImGuiCol_FrameBgActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TitleBg", &style.Colors[ImGuiCol_TitleBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TitleBgActive", &style.Colors[ImGuiCol_TitleBgActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TitleBgCollapsed", &style.Colors[ImGuiCol_TitleBgCollapsed].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("MenuBarBg", &style.Colors[ImGuiCol_MenuBarBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ScrollbarBg", &style.Colors[ImGuiCol_ScrollbarBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ScrollbarGrab", &style.Colors[ImGuiCol_ScrollbarGrab].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ScrollbarGrabHovered", &style.Colors[ImGuiCol_ScrollbarGrabHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ScrollbarGrabActive", &style.Colors[ImGuiCol_ScrollbarGrabActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("CheckMark", &style.Colors[ImGuiCol_CheckMark].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("SliderGrab", &style.Colors[ImGuiCol_SliderGrab].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("SliderGrabActive", &style.Colors[ImGuiCol_SliderGrabActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Button", &style.Colors[ImGuiCol_Button].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ButtonHovered", &style.Colors[ImGuiCol_ButtonHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ButtonActive", &style.Colors[ImGuiCol_ButtonActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Header", &style.Colors[ImGuiCol_Header].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("HeaderHovered", &style.Colors[ImGuiCol_HeaderHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("HeaderActive", &style.Colors[ImGuiCol_HeaderActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Separator", &style.Colors[ImGuiCol_Separator].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("SeparatorHovered", &style.Colors[ImGuiCol_SeparatorHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("SeparatorActive", &style.Colors[ImGuiCol_SeparatorActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ResizeGrip", &style.Colors[ImGuiCol_ResizeGrip].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ResizeGripHovered", &style.Colors[ImGuiCol_ResizeGripHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ResizeGripActive", &style.Colors[ImGuiCol_ResizeGripActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("Tab", &style.Colors[ImGuiCol_Tab].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TabHovered", &style.Colors[ImGuiCol_TabHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TabActive", &style.Colors[ImGuiCol_TabActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TabUnfocused", &style.Colors[ImGuiCol_TabUnfocused].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TabUnfocusedActive", &style.Colors[ImGuiCol_TabUnfocusedActive].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("DockingPreview", &style.Colors[ImGuiCol_DockingPreview].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("DockingEmptyBg", &style.Colors[ImGuiCol_DockingEmptyBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("PlotLines", &style.Colors[ImGuiCol_PlotLines].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("PlotLinesHovered", &style.Colors[ImGuiCol_PlotLinesHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("PlotHistogram", &style.Colors[ImGuiCol_PlotHistogram].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("PlotHistogramHovered", &style.Colors[ImGuiCol_PlotHistogramHovered].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TableHeaderBg", &style.Colors[ImGuiCol_TableHeaderBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TableBorderStrong", &style.Colors[ImGuiCol_TableBorderStrong].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TableBorderLight", &style.Colors[ImGuiCol_TableBorderLight].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TableRowBg", &style.Colors[ImGuiCol_TableRowBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TableRowBgAlt", &style.Colors[ImGuiCol_TableRowBgAlt].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("TextSelectedBg", &style.Colors[ImGuiCol_TextSelectedBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("DragDropTarget", &style.Colors[ImGuiCol_DragDropTarget].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("NavHighlight", &style.Colors[ImGuiCol_NavHighlight].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("NavWindowingHighlight", &style.Colors[ImGuiCol_NavWindowingHighlight].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("NavWindowingDimBg", &style.Colors[ImGuiCol_NavWindowingDimBg].x, 0.0f, 1.0f);
			ImGui::SliderFloat4("ModalWindowDimBg", &style.Colors[ImGuiCol_ModalWindowDimBg].x, 0.0f, 1.0f);
		


			ImGui::End();
		};
		addGuiWindow(lambda);
	
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