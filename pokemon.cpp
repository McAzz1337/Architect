#include "pokemon.h"



glm::vec2 Pokemon::uvOffsets[Sprite::NONE];
glm::vec2 Pokemon::spriteSize;
glm::vec2 Pokemon::spriteSheetSize;

Pokemon::Pokemon() {

}

Pokemon::Pokemon(glm::vec2 uv) {
	uvs[Sprite::FRONT] = uv + uvOffsets[Sprite::FRONT];
	uvs[Sprite::FRONT_SHINY] = uv + uvOffsets[Sprite::FRONT_SHINY];
	uvs[Sprite::BACK] = uv + uvOffsets[Sprite::BACK];
	uvs[Sprite::BACK_SHINY] = uv + uvOffsets[Sprite::BACK_SHINY];
}

Pokemon::~Pokemon() {

}

void Pokemon::setSprite(Sprite sprite) { 
	
	using namespace archt;
	this->sprite = sprite;

	glm::vec2 coord = uvs[sprite];

	Vertex* verteces = vbo->getData();
	int size = vbo->getSize();
	for (int i = 0; i < size; i += size) {

		verteces[i].uv = coord;
		verteces[i + 1].uv = coord + glm::vec2(spriteSize.x, 0.0f);
		verteces[i + 2].uv = coord + spriteSize;
		verteces[i + 3].uv = coord + glm::vec2( 0.0f, spriteSize.y);
	}

}

void Pokemon::setUvs(const glm::vec2& uv) {
	uvs[Sprite::FRONT] = uv + uvOffsets[Sprite::FRONT];
	uvs[Sprite::FRONT_SHINY] = uv + uvOffsets[Sprite::FRONT_SHINY];
	
	uvs[Sprite::FRONT_ALT] = uv + uvOffsets[Sprite::FRONT_ALT];
	uvs[Sprite::FRONT_ALT_SHINY] = uv + uvOffsets[Sprite::FRONT_ALT_SHINY];

	uvs[Sprite::BACK] = uv + uvOffsets[Sprite::BACK];
	uvs[Sprite::BACK_SHINY] = uv + uvOffsets[Sprite::BACK_SHINY];
	setSprite(sprite);
}

void Pokemon::translateUv(const glm::vec2& v) {
	archt::Vertex* verteces = vbo->getData();
	int size = vbo->getSize();
	for (int i = 0; i < size; i += size) {
		verteces[i].uv +=	v;
		verteces[i + 1].uv += v;
		verteces[i + 2].uv += v;
		verteces[i + 3].uv += v;
	}
}

void Pokemon::snapUvs() {
	
	archt::Vertex* verteces = vbo->getData();
	int size = vbo->getSize();
	const glm::vec2 uv = verteces[0].uv;
	
	float restX = fmod(uv.x, spriteSize.x);

	glm::vec2 translation;
	
	if (restX < spriteSize.x)
		translation.x = uv.x - 1.0f / spriteSheetSize.x;
	else
		translation.x = -restX;

	translateUv(translation);
}



void Pokemon::setUVOffsets(glm::vec2* offsets) {
	for (int i = 0; i < Sprite::NONE; i++) {
		uvOffsets[i] = offsets[i];
	}
}

void Pokemon::setSpriteSize(const glm::vec2& size) {
	spriteSize = size;
}

void Pokemon::setSpriteSheetSize(const glm::vec2& size) {
	spriteSheetSize = size;
}


const glm::vec2& Pokemon::getSpriteSheetSize() {
	return spriteSheetSize;
}