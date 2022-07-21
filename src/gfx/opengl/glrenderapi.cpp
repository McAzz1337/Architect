#include "glrenderapi.h"

#include "glinclude.h"

#include "glshaderconstants.h"

namespace archt {

	std::string GLRenderAPI::vendor = "N/A";
	std::string GLRenderAPI::version = "N/A";
	int GLRenderAPI::availableMemory = 0;
	int GLRenderAPI::maxTextures = 32;
	int GLRenderAPI::maxMatrices = 100;
	GLWindow* GLRenderAPI::window = nullptr;


	uint32_t GLRenderAPI::clearMask = 0;


	GLWindow* GLRenderAPI::init() {

		if (glfwInit() != GLFW_TRUE) {
			printf("Failed to initialize GLFW!\n");
			__debugbreak();
		}


		window = new GLWindow("Architect", 0, 0, 1080, 720);

		if (glewInit() != GLEW_OK) {
			printf("Failed to initialize GLEW!\n");
			__debugbreak();
		}

		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableMemory);
		
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
		GLShaderConstants::setConstant(GLShaderConstants::MAX_TEXTURES, &maxTextures);
		
		
		GLShaderConstants::setConstant(GLShaderConstants::MAX_MATRICES, &maxMatrices);


		vendor = std::string((char*) glGetString(GL_VENDOR));
		version = std::string((char*) glGetString(GL_VERSION));

		std::string title = "Architect | " + vendor + " | " + version;

		window->setTitle(title.c_str());

		return window;
	}

	void GLRenderAPI::terminate() {

	}

	void GLRenderAPI::enable(uint32_t feature) {
		glEnable(feature);
	}

	void GLRenderAPI::disable(uint32_t feature) {
		glDisable(feature);
	}

	void GLRenderAPI::blendFunc(uint32_t sFactor, uint32_t dFactor) {
		glBlendEquation(GL_ADD);
		glBlendFunc(sFactor, dFactor);
	}

	void GLRenderAPI::setCullFace(uint32_t frontFace, uint32_t cullFace) {
		glEnable(GL_CULL_FACE);
		glFrontFace(frontFace);
		glCullFace(cullFace);
	}

	void GLRenderAPI::setClearMask(uint32_t mask) {
		clearMask = mask;
	}

	void GLRenderAPI::addToClearMask(uint32_t mask) {
		clearMask |= mask;
	}

	void GLRenderAPI::removeFromClearMask(uint32_t mask) {
		clearMask &= ~mask;
	}

	int GLRenderAPI::getMaxTextureCount() {
		return maxTextures;
	}

	int GLRenderAPI::getMaxMatricesCount() {
		return maxMatrices;
	}

}