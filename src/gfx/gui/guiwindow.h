#pragma once

#include <functional>

namespace archt {
	class GuiWindow {

		std::function<void()> renderFunc;

	public:
		GuiWindow();
		GuiWindow(std::function<void()> renderFunc);
		~GuiWindow();


		void render();

		void setRenderFunc(std::function<void()> renderFunc);
	};
}