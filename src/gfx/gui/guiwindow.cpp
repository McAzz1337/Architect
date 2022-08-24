#include "guiwindow.h"


namespace archt {


    GuiWindow::~GuiWindow() {

    }

   

    GuiWindowVoid::GuiWindowVoid(std::function<void()> func) : f(func) {}

    void GuiWindowVoid::render() {
        f();
    }
}