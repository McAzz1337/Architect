#include <iostream>

// archt misc
#include "src/chronos/deltatime.h"
#include "src/fileio.h"
#include "src/filesystem/filemanager.h"
#include "src/input/input.h"

// archt graphics
#include "src/gfx/opengl/camera.h"
#include "src/gfx/opengl/glmesh.h"
#include "src/gfx/opengl/glrenderapi.h"
#include "src/gfx/opengl/glrenderer2d.h"
#include "src/gfx/opengl/glshader.h"
#include "src/gfx/opengl/gltexture.h"
#include "src/gfx/opengl/glwindow.h"

//glm
#include <glm/gtx/transform.hpp>

// std
#include <math.h>

// pokememe
#include "pokemon.h"
#include "spritesheet.h"




int main() {

	using namespace archt;


	GLWindow* window = GLRenderAPI::init();
	GLRenderer2D::init();
	Input::init();

	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 1000.0f);


	//GLShader* shader = (GLShader*) FileManager::instance.loadFile("src/assets/shaders/shader/shader", FileManager::FileType::GL_SHADER_T);
	GLShader* fastShader = new GLShader("src/assets/shaders/fastshader/fastshader"); 
	GLShader* transferShader = new GLShader("src/assets/shaders/transfer/transfer"); 

	Uniformbuffer* uniformBuffer = new Uniformbuffer(nullptr, 4 * 16 * 1000);
	fastShader->registerUniformBuffer(uniformBuffer);
	transferShader->registerUniformBuffer(uniformBuffer);

	int meshSize = 251;// GLRenderAPI::getMaxMatricesCount();

	Pokemon pokemon;
	Pokemon* pokemons = new Pokemon[meshSize];

	SpriteSheet spriteSheet("src/assets/img/pokememes.png");
	pokemon.setSpriteSheet(&spriteSheet);
	pokemon.setShader(fastShader);


#pragma region BUFFER_SETUP
	{
		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize]{
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }, 0.0f, 0.0f),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 0.0f, 0.0f),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }, 0.0f, 0.0f),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f }, 0.0f, 0.0f)
		};




		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize]{
			0, 1, 2,
			0, 2, 3
		};

		pokemon.setVbo(verteces, vSize);
		pokemon.setIbo(indeces, iSize);

		for (int i = 0; i < meshSize; i++) {
			pokemons[i].setSpriteSheet(&spriteSheet);
			pokemons[i].setShader(fastShader);
			pokemons[i].setVbo(verteces, vSize);
			pokemons[i].setIbo(indeces, iSize);
		}


	}
#pragma endregion BUFFER_SETUP

	int size = 56;
	int footprintSize = 16;
	glm::vec2 spriteSheetSize = spriteSheet.getSize();
	glm::vec2 spriteSize = spriteSheet.normalizeUv(size, size);
	glm::ivec2 strides = { 171, 188 };
	glm::vec2 pixelSizes = spriteSheet.getPixelSizes();



#pragma region UV_SETUP
	{
		pokemon.setSpriteSize(spriteSize);
		pokemon.setFootprintSize(spriteSheet.normalizeUv(footprintSize, footprintSize));

		for (int i = 0; i < meshSize; i++) {
			pokemons[i].setSpriteSize(spriteSize);
			pokemons[i].setFootprintSize(spriteSheet.normalizeUv(footprintSize, footprintSize));
		}

		glm::vec2 offsets[Pokemon::Sprite::NONE];
		offsets[Pokemon::Sprite::FRONT] = spriteSheet.normalizeUv(1, 18);
		offsets[Pokemon::Sprite::FRONT_SHINY] = spriteSheet.normalizeUv(2 + size, 18);

		offsets[Pokemon::Sprite::FRONT_ALT] = spriteSheet.normalizeUv(1, 19 + size);
		offsets[Pokemon::Sprite::FRONT_ALT_SHINY] = spriteSheet.normalizeUv(2 + size, 19 + size);


		offsets[Pokemon::Sprite::BACK] = spriteSheet.normalizeUv(1, 2 * size + 20);
		offsets[Pokemon::Sprite::BACK_SHINY] = spriteSheet.normalizeUv(2 + size, 2 * size + 20);

		offsets[Pokemon::Sprite::FOOTPRINT] = spriteSheet.normalizeUv(115, 1);

		pokemon.loadOffset("src/assets/img/pokememes_offset.txt");
		for (int i = 0; i < meshSize; i++) {
			pokemons[i].loadOffset("src/assets/img/pokememes_offset.txt");

			int x = i % 10;
			int y = (i - x) / 10;

			pokemons[i].setUvs(spriteSheet.normalizeUv(x * strides.x, y * strides.y));

			pokemons[i].setSprite(Pokemon::Sprite::FRONT);
			pokemons[i].translate({ (float) x, (float) y, 0.0f });
		}
	}
	pokemon.setUvs({ 0.0f, 0.0f });
	pokemon.setSprite(Pokemon::Sprite::FRONT);
#pragma endregion UV_SETUP

	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);



	DeltaTime delta;
	double elapsed = 0;

	double transferDuration = 2.0;
	double transferProgress = 0.0;
	bool inTransfer = false;

	while (true) {
		delta.update();

		elapsed += delta.getSeconds();
		//printf("elapsed : %f\n", elapsed);


		window->pollEvents();

#pragma region CONTROLS
		bool shift = Input::isPress(GLFW_KEY_LEFT_SHIFT) || Input::isHeld(GLFW_KEY_LEFT_SHIFT);
		bool control = Input::isPress(GLFW_KEY_LEFT_CONTROL) || Input::isHeld(GLFW_KEY_LEFT_CONTROL);
		float translation = 0.03f;
		if (control) {
			translation = 0.003f;
		}
		else if (shift) {
			translation = 0.3f;
		}


		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			cam.translate({ 0.0f, 0.0f, -translation });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			cam.translate({ 0.0f, 0.0f, translation });

		}


		if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			cam.translate({ -translation, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			cam.translate({ translation, 0.0f, 0.0f });
		}

		if (Input::isPress(GLFW_KEY_E) || Input::isHeld(GLFW_KEY_E)) {
			cam.translate({ 0.0f, translation, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_F) || Input::isHeld(GLFW_KEY_F)) {
			cam.translate({ 0.0f, -translation, 0.0f });
		}



		float dx = size / 20.0f;
		float dy = size / 20.0f;
		if (control) {
			dx = 0.1f / spriteSheetSize.x;
			dy = 0.1f / spriteSheetSize.y;
		}
		else if (shift) {
			dx = size / 60.0f;
			dy = size / 60.0f;
		}

		static bool backSpaceWasPressed = false;
		if ((Input::isPress(GLFW_KEY_BACKSPACE) || Input::isHeld(GLFW_KEY_BACKSPACE)) && !backSpaceWasPressed) {
			int sprite = pokemon.getSprite() + 1;
			if (sprite == Pokemon::Sprite::NONE) {
				sprite = Pokemon::Sprite::FRONT;
			}
			for (int i = 0; i < meshSize; i++) {
				pokemons[i].setSprite((Pokemon::Sprite) sprite);
			}
			pokemon.setSprite((Pokemon::Sprite) sprite);
			backSpaceWasPressed = true;
		}
		else if (Input::isRelease(GLFW_KEY_BACKSPACE)) {
			backSpaceWasPressed = false;
		}


		if (Input::isPress(GLFW_KEY_RIGHT) || Input::isHeld(GLFW_KEY_RIGHT)) {
			pokemon.translateUv(glm::vec2(dx, 0.0f));
		}
		else if (Input::isPress(GLFW_KEY_LEFT) || Input::isHeld(GLFW_KEY_LEFT)) {
			pokemon.translateUv(glm::vec2(-dx, 0.0f));
		}

		if (Input::isPress(GLFW_KEY_UP) || Input::isHeld(GLFW_KEY_UP)) {
			pokemon.translateUv(glm::vec2(0.0f, -dy));
		}
		else if (Input::isPress(GLFW_KEY_DOWN) || Input::isHeld(GLFW_KEY_DOWN)) {
			pokemon.translateUv(glm::vec2(0.0f, dy));
		}
#pragma endregion CONTROLS


		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);


		//GLRenderer2D::submit(&pokemon);
		

		static glm::vec2 uvOffset(0.0f, 0.0f);
		if (!inTransfer && elapsed >= 3.0) {
			int sprite = pokemons[0].getSprite();
			int nextSprite = sprite + 1;
			if (nextSprite == Pokemon::Sprite::NONE) {
				nextSprite = Pokemon::Sprite::FRONT;
			}
			
			const glm::vec2& uv = pokemons[0].getUvOffset((Pokemon::Sprite) sprite);
			const glm::vec2& nextUv = pokemons[0].getUvOffset((Pokemon::Sprite) nextSprite);
			uvOffset = nextUv - uv;
		
			for (int i = 0; i < meshSize; i++) {
				pokemons[i].setShader(transferShader);
			}
			transferProgress = 0.0;
			inTransfer = true;
			elapsed -= 3.0;
		}
		else if (inTransfer) {
			transferProgress = elapsed / transferDuration;

			if (elapsed >= transferDuration) {

				int nextSprite = pokemons[0].getSprite() + 1;
				if (nextSprite == Pokemon::Sprite::NONE) {
					nextSprite = Pokemon::Sprite::FRONT;
				}
				for (int i = 0; i < meshSize; i++) {
					pokemons[i].setShader(fastShader);
					pokemons[i].setSprite((Pokemon::Sprite) nextSprite);
				}
				
				elapsed -= transferDuration;
				inTransfer = false;
			}
		}

		

		

		if (inTransfer) {
			transferShader->bind();
			
			
			
			glm::vec2 off(0.0f, 0.0f);
			transferShader->setUniform2f("uvOffset", (float*) &off);
			transferShader->setUniform1f("alpha", (float) (1.0 - transferProgress));

			for (int i = 0; i < meshSize; i++) {
				GLRenderer2D::submit(&pokemons[i]);
			}
			GLRenderer2D::render();
			GLRenderer2D::flush();
			GLRenderer2D::endScene();
			GLRenderer2D::beginScene(&cam);

			
			
			transferShader->setUniform2f("uvOffset", (float*) &uvOffset);
			transferShader->setUniform1f("alpha", (float) transferProgress);
			for (int i = 0; i < meshSize; i++) {
				GLRenderer2D::submit(&pokemons[i]);
			}
			GLRenderer2D::render();
			GLRenderer2D::flush();
			GLRenderer2D::endScene();
		}

			
		else {
			for (int i = 0; i < meshSize; i++) {
				GLRenderer2D::submit(&pokemons[i]);
			}
			GLRenderer2D::render();
			GLRenderer2D::flush();
			GLRenderer2D::endScene();
		}

	


		//printf("Available Memory: %i\n", GLRenderAPI::queryAvailableMemory());
		//printf("Allocated Memory: %i\n", GLRenderAPI::queryTotalMemory() - GLRenderAPI::queryAvailableMemory());
		window->swapBuffer();

		if (window->shouldClose()) {
			break;
		}
	}


	GLRenderer2D::terminate();
	FileManager::instance.deleteAllFiles();

	return 0;
}