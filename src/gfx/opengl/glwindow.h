#pragma once
#include "glinclude.h"


namespace archt {



	class GLWindow {

		GLFWwindow* window = nullptr;
		const char* title;
		int x, y, w, h;

	public:

		GLWindow();
		GLWindow(const char* title, int x, int y, int w, int h);
		~GLWindow();

		void makeContextCurrent() const;

		void pollEvents();
		bool shouldClose();
		void swapBuffer();

		void setTitle(const char* name);

	};
}