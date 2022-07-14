#pragma once
#include <typeindex>

#include "glrenderer2d.h"

namespace archt {


	class GLRenderAPI {


		static uint32_t clearMask;

	public:
		GLRenderAPI() = delete;

		static void enable(uint32_t feature);
		static void disable(uint32_t feature);

		static void blendFunc(uint32_t sFactor, uint32_t dFactor);

		static void setClearMask(uint32_t mask);
		static void addToClearMask(uint32_t mask);
		static void removeFromClearMask(uint32_t mask);

		friend void GLRenderer2D::clear();


	};
}