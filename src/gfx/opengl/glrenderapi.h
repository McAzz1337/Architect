#pragma once
#include <typeindex>

#include "glrenderer2d.h"
#include "glwindow.h"

namespace archt {


	class GLRenderAPI {

		static std::string vendor;
		static std::string version;
		static std::string model;
		static std::string shaderLanguageVersion;

		static int availableMemory;
		static int totalMemory;
		static uint32_t clearMask;

		static GLWindow* window;

		static int maxTextures;
		static int maxMatrices;

	public:
		GLRenderAPI() = delete;

		static GLWindow* init();
		static void terminate();
		
		static void enable(uint32_t feature);
		static void disable(uint32_t feature);

		static void blendFunc(uint32_t sFactor, uint32_t dFactor);
		static void setCullFace(uint32_t frontFace, uint32_t cullFace);

		static void setClearMask(uint32_t mask);
		static void addToClearMask(uint32_t mask);
		static void removeFromClearMask(uint32_t mask);


		static int queryAvailableMemory();
		static int queryTotalMemory();
		static int getMaxTextureCount();
		static int getMaxMatricesCount();

		static void createGuiInfoWindow();

		friend void GLRenderer2D::clear();
		friend void GLRenderer2D::startBatch();
		friend void GLRenderer2D::init();


	};
}