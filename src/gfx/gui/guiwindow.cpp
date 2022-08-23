#include "guiwindow.h"


namespace archt {


    GuiWindowBase::~GuiWindowBase() {

    }

   

    //GuiWindowVoid::GuiWindowVoid(std::function<void()> renderFunc) : func(renderFunc) {
    //
    //}
    //GuiWindowVoid::~GuiWindowVoid() {
    //
    //}
    //
    //void GuiWindowVoid::render() {
    //    func();
    //}

    GuiWindowVoid::GuiWindowVoid(std::function<void()> func) : f(func) {}

    void GuiWindowVoid::render() {
        f();
    }
}