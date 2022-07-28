#include "glrenderapi.h"

#include "glinclude.h"
#include "gldebug.h"

#include "glshaderconstants.h"

namespace archt {

	std::string GLRenderAPI::vendor = "N/A";
	std::string GLRenderAPI::version = "N/A";
	std::string GLRenderAPI::model = "N/A";
	std::string GLRenderAPI::shaderLanguageVersion = "N/A";

	
	int GLRenderAPI::availableMemory = 0;
	int GLRenderAPI::totalMemory = 0;
	int GLRenderAPI::maxTextures = 32;
	int GLRenderAPI::maxMatrices = 256;
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
		glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &totalMemory);
		

		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
		GLShaderConstants::setConstant(GLShaderConstants::MAX_TEXTURES, &maxTextures);
		int maxVec4 = 0;
		glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVec4);
		maxMatrices = 1000;
		
		int temp = 256;
		GLShaderConstants::setConstant(GLShaderConstants::MAX_MATRICES, &temp);


		vendor = std::string((char*) glGetString(GL_VENDOR));
		version = std::string((char*) glGetString(GL_VERSION));
		model = std::string((char*) glGetString(GL_RENDERER));
		shaderLanguageVersion = std::string((char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		std::string title = "Architect | " + vendor + " | " + version + " | " + model + " | " + shaderLanguageVersion + " | Memory: " + std::to_string(totalMemory);

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
		glBlendFunc(sFactor, dFactor);
		CALL(glBlendEquation(GL_FUNC_ADD));
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

	int GLRenderAPI::queryAvailableMemory() {
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableMemory);
		return availableMemory;
	}

	int GLRenderAPI::queryTotalMemory() {
		return totalMemory;
	}

	int GLRenderAPI::getMaxTextureCount() {
		return maxTextures;
	}

	int GLRenderAPI::getMaxMatricesCount() {
		return maxMatrices;
	}

}