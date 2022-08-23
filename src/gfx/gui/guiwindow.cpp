#include "guiwindow.h"


namespace archt{


	GuiWindow::GuiWindow() {
	}

	GuiWindow::GuiWindow(std::function<void()> renderFunc) : renderFunc(renderFunc) {
	}

	GuiWindow::~GuiWindow() {
	}

	void GuiWindow::render() {
		renderFunc();
	}

	void GuiWindow::setRenderFunc(std::function<void()> renderFunc) {
		this->renderFunc = renderFunc;
	}
}