#pragma once
#include "glinclude.h"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <vector>

namespace archt {

	typedef void (*ViewportCallback) (int width, int height);

	void keyCallback(GLFWwindow* window, int key, int scan, int action, int mod);

	class GLWindow {

		friend void keyCallback(GLFWwindow* window, int key, int scan, int action, int mod);

		std::vector<ViewportCallback> viewportCallbacks;

		GLFWwindow* window = nullptr;
		const char* title;
		int x, y, w, h;
		mutable bool fullScreen = false;
		int refreshRate = 0;

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

		void toggleFullscreen() const;

		void centerOnScreen()const;
		void hide() const;
		void show() const;

		void addViewportCallback(ViewportCallback callback);

		inline GLFWwindow* getHandle() const { return window; }
		inline glm::ivec2 getSize() const { return glm::ivec2(w, h); }
		inline glm::ivec4 getBounds() const { return glm::ivec4(x, y, w, h); }
	};
}