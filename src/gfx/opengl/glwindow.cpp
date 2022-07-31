#include "glwindow.h"

#include "../../input/input.h"

#include <iostream>

namespace archt {

	void keyCallback(GLFWwindow* window, int key, int scan, int action, int mod) {

		if (key == GLFW_KEY_ESCAPE) {
			glfwSetWindowShouldClose(window, 1);
		}
		else {
			switch (action) {
				case GLFW_PRESS: 
					Input::press(key);
					break;
				case GLFW_REPEAT:
					Input::hold(key);
					break;
				case GLFW_RELEASE:
					Input::release(key); 
					break;
				default:
					printf("Unimplemented key action : %i\n", action);
					break;
			}
		}
	}

	GLWindow::GLWindow() {

	}

	GLWindow::GLWindow(const char* title, int x, int y, int w, int h)
		: title(title), x(x), y(y), w(w), h(h) {

		
		window = glfwCreateWindow(w, h, title, nullptr, nullptr);
		glfwMakeContextCurrent(window);

		glfwSetWindowPos(window, x, y);

		glfwSetKeyCallback(window, keyCallback);
	}



	GLWindow::~GLWindow() {
		if (window)
			glfwDestroyWindow(window);
		
		glfwTerminate();
	}

	void GLWindow::makeContextCurrent() const {
		glfwMakeContextCurrent(window);
	}


	void GLWindow::pollEvents() {
		glfwPollEvents();
	}

	bool GLWindow::shouldClose() {
		return glfwWindowShouldClose(window) == 1;
	}

	void GLWindow::swapBuffer() {
		glfwSwapBuffers(window);
	}


	void GLWindow::setTitle(const char* name) {
		glfwSetWindowTitle(window, name);
	}


}