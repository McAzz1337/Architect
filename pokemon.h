#pragma once

#include "src/gfx/opengl/glmesh.h";
#include <glm/vec2.hpp>

class Pokemon : public archt::GLMesh {

public:
	enum Sprite {
		
		FRONT,
		FRONT_SHINY,
		FRONT_ALT,
		FRONT_ALT_SHINY,
		BACK,
		BACK_SHINY,
		NONE
	};

private:
	static glm::vec2 uvOffsets[Sprite::NONE];
	static glm::vec2 spriteSize;
	static glm::vec2 spriteSheetSize;


	int index = 0;
	glm::vec2 uvs[Sprite::NONE];
	Sprite sprite = Sprite::FRONT;

public:
	Pokemon();
	Pokemon(glm::vec2 uv);
	~Pokemon();

	void setSprite(Sprite sprite);

	void setUvs(const glm::vec2& uv);
	void translateUv(const glm::vec2& v);
	void snapUvs();

	inline Sprite getSprite() const { return sprite; }

	static void setUVOffsets(glm::vec2* offsets);
	static void setSpriteSize(const glm::vec2& size);
	static void setSpriteSheetSize(const glm::vec2& size);

	static const glm::vec2& getSpriteSheetSize();

};
