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

// audio
#include "src/audio/openal/sounddevice.h"
#include "src/audio/openal/audiobuffer.h"
#include "src/audio/openal/soundsource.h"


//glm
#include <glm/gtx/transform.hpp>

// std
#include <math.h>

// pokememe
#include "pokemon.h"
#include "spritesheet.h"


double scrollTime = 10.0;
float scrollY = 0.0f;
float step = 0.0f;

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

	int pokemonCount = 251;// GLRenderAPI::getMaxMatricesCount();

	Pokemon pokemon;
	Pokemon* pokemons = new Pokemon[pokemonCount];
	Pokemon trainer;

	SpriteSheet* trainerSheet = new SpriteSheet("src/assets/img/trainers.png");
	SpriteSheet* spriteSheet = new SpriteSheet("src/assets/img/pokememes.png");
	
	
	pokemon.setSpriteSheet(spriteSheet);
	pokemon.setShader(fastShader);

	trainer.setSpriteSheet(trainerSheet);
	trainer.setShader(fastShader);

#pragma region SOUND_SETUP
	SoundDevice::init();
	AudioBuffer* music = new AudioBuffer("D:/GithubRepos/Architect/src/assets/audio/pokemon-rgby-wild-pokemon-battle-music.wav");
	AudioBuffer* stealYaBitch = new AudioBuffer("D:/GithubRepos/Architect/src/assets/audio/stealyabitch.wav");
	SoundSource* source = new SoundSource(music);
	SoundSource* source1 = new SoundSource(stealYaBitch);

#pragma endregion SOUND_SETUP


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
		
		trainer.setVbo(verteces, vSize);
		trainer.setIbo(indeces, iSize);
		
		for (int i = 0; i < pokemonCount; i++) {
			pokemons[i].setSpriteSheet(spriteSheet);
			pokemons[i].setShader(fastShader);
			pokemons[i].setVbo(verteces, vSize);
			pokemons[i].setIbo(indeces, iSize);
		}
		

	}
#pragma endregion BUFFER_SETUP

	int size = 56;
	int footprintSize = 16;
	glm::vec2 spriteSheetSize = spriteSheet->getSize();
	glm::vec2 spriteSize = spriteSheet->normalizeUv(size, size);
	glm::ivec2 strides = { 171, 188 };
	glm::vec2 pixelSizes = spriteSheet->getPixelSizes();



#pragma region UV_SETUP
	{
		pokemon.setSpriteSize(spriteSize);
		pokemon.setFootprintSize(spriteSheet->normalizeUv(footprintSize, footprintSize));
		
		trainer.setSpriteSize(trainerSheet->normalizeUv(size, size));
		trainer.setFootprintSize({ 0.0f, 0.0f });

		for (int i = 0; i < pokemonCount; i++) {
			pokemons[i].setSpriteSize(spriteSize);
			pokemons[i].setFootprintSize(spriteSheet->normalizeUv(footprintSize, footprintSize));
		}
		

		glm::vec2 offsets[Pokemon::Sprite::NONE];
		offsets[Pokemon::Sprite::FRONT] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::FRONT_SHINY] = glm::vec2(0.0f, 0.0f);
		
		offsets[Pokemon::Sprite::FRONT_ALT] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::FRONT_ALT_SHINY] = glm::vec2(0.0f, 0.0f);
		
		
		offsets[Pokemon::Sprite::BACK] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::BACK_SHINY] = glm::vec2(0.0f, 0.0f);
		
		offsets[Pokemon::Sprite::FOOTPRINT] = glm::vec2(0.0f, 0.0f);
		
		pokemon.loadOffset("src/assets/img/pokememes_offset.txt");
		trainer.setUVOffsets(offsets);

		int y = 0;
		for (int i = 0; i < pokemonCount; i++) {
			pokemons[i].loadOffset("src/assets/img/pokememes_offset.txt");

			int x = i % 10;
			y = (i - x) / 10;


			pokemons[i].setUvs(spriteSheet->normalizeUv(x * strides.x, y * strides.y));

			pokemons[i].setSprite(Pokemon::Sprite::FRONT);
			pokemons[i].translate({ (float) x - 4.5f, (float) y, -5.0f });
		}
		scrollY = (float) y / -100.0f;
		step = scrollY / (float) scrollTime;
	}
	pokemon.setUvs({ 0.0f, 0.0f });
	pokemon.setSprite(Pokemon::Sprite::FRONT);
	
	trainer.setUvs(trainerSheet->normalizeUv(0, 10 * size));
	trainer.setSprite(Pokemon::Sprite::FRONT);
	trainer.translate({ -1.5f, 0.0f, 0.0f });

#pragma endregion UV_SETUP

	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);



	DeltaTime delta;
	double elapsed = 0;

	source->play();
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
			for (int i = 0; i < pokemonCount; i++) {
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


		bool scroll = elapsed > 1.0;
		static bool first = true;
		
		if (elapsed > scrollTime) {
			if (first) {
				source->stop();
				source1->play();
				first = false;
				goto RENDER;
			}
			else {
				trainer.translate({ 1.0f / 250.0f, 0.0f, 0.0f });
				GLRenderer2D::submit(&trainer);
			}
		}
		else {
			for (int i = 0; i < pokemonCount; i++) {
				GLRenderer2D::submit(&pokemons[i]);
				if (scroll) pokemons[i].translate({ 0.0f, step, 0.0f });
			}
		}

		RENDER:
		GLRenderer2D::render();
		GLRenderer2D::flush();
		GLRenderer2D::endScene();

	


		//printf("Available Memory: %i\n", GLRenderAPI::queryAvailableMemory());
		//printf("Allocated Memory: %i\n", GLRenderAPI::queryTotalMemory() - GLRenderAPI::queryAvailableMemory());
		window->swapBuffer();

		if (window->shouldClose() || elapsed > 15.0) {
			break;
		}
	}


	SoundDevice::terminate();
	GLRenderer2D::terminate();
	FileManager::instance.deleteAllFiles();

	return 0;
}