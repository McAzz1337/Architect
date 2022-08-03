#pragma once
#include "glinclude.h"
#include <glm/vec2.hpp>
#include <vector>

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
		void setSize(int width, int height);



		inline GLFWwindow* getHandle() const { return window; }
		inline glm::ivec2 getSize() const { return glm::ivec2(w, h); }

	};
}