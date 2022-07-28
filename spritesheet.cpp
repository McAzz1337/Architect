#include "spritesheet.h"


SpriteSheet::SpriteSheet() {

}

SpriteSheet::SpriteSheet(const std::string& path) {
	texture = new archt::GLTexture(path);
	glm::ivec2 size = texture->getSize();
	pixelX = 1.0f / (float) size.x;
	pixelY = 1.0f / (float) size.y;
}

SpriteSheet::~SpriteSheet() {
	if (texture)
		delete texture;
}

glm::vec2 SpriteSheet::normalizeUv(int x, int y) {
	
	if (!texture)
		return { -1.0f, -1.0f };

	glm::vec2 uv(0.0f, 0.0f);
	glm::ivec2 sheetSize = texture->getSize();

	if (x != 0) {
		uv.x = (float) x / (float) sheetSize.x;
	}

	if (y != 0) {
		uv.y = (float) y / (float) sheetSize.y;
	}

	return uv;
}

glm::vec2 SpriteSheet::getSize() const {
	glm::ivec2 size = texture->getSize();
	return { (float) size.x, (float) size.y };
}
