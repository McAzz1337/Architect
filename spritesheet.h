#pragma once
#include <glm/vec2.hpp>

#include "src/gfx/opengl/gltexture.h"


class SpriteSheet {

	archt::GLTexture* texture = nullptr;
	float pixelX = 0.0f;
	float pixelY = 0.0f;


public:
	SpriteSheet();
	SpriteSheet(const std::string& path);
	~SpriteSheet();

	glm::vec2 normalizeUv(int x = 0, int y = 0);

	glm::vec2 getSize() const;

	inline archt::GLTexture* getTexture() const { return texture; }
	inline glm::vec2 getPixelSizes() const { return glm::vec2(pixelX, pixelY); }
};