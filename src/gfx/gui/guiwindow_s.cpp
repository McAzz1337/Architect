#include "gui_s.h"


namespace archt {


    BaseWindow::~BaseWindow() {

    }

   

    GuiWindow_t::GuiWindow_t(std::function<void()> renderFunc) : func(renderFunc) {

    }
    GuiWindow_t::~GuiWindow_t() {

    }

    void GuiWindow_t::render() {
        func();
    }

}