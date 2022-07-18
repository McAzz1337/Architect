#pragma once
#include <typeindex>

#include "glrenderer2d.h"

namespace archt {


	class GLRenderAPI {

		static std::string vendor;
		static std::string version;
		static int availableMemory;
		static uint32_t clearMask;

		static int maxTextures;

	public:
		GLRenderAPI() = delete;

		static void init();
		static void terminate();


		static void enable(uint32_t feature);
		static void disable(uint32_t feature);

		static void blendFunc(uint32_t sFactor, uint32_t dFactor);

		static void setClearMask(uint32_t mask);
		static void addToClearMask(uint32_t mask);
		static void removeFromClearMask(uint32_t mask);

		friend void GLRenderer2D::clear();

		static int getMaxTextureCount();

	};
}