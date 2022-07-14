#include "glrenderapi.h"

#include "glinclude.h"

namespace archt {


	uint32_t GLRenderAPI::clearMask = 0;




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
}