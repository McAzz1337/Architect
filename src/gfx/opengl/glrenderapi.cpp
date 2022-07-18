#include "glrenderapi.h"

#include "glinclude.h"

#include "glshaderconstants.h"

namespace archt {

	std::string GLRenderAPI::vendor = "N/A";
	std::string GLRenderAPI::version = "N/A";
	int GLRenderAPI::availableMemory = 0;
	int GLRenderAPI::maxTextures = 32;


	uint32_t GLRenderAPI::clearMask = 0;


	void GLRenderAPI::init() {
		vendor = std::string((char*) glGetString(GL_VENDOR));
		version = std::string((char*) glGetString(GL_VERSION));
		
		glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &availableMemory);
		
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures);
		GLShaderConstants::setConstant(GLShaderConstants::MAX_TEXTURES, &maxTextures);
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

}