#include <iostream>

#if 0

// archt misc
#include "src/chronos/deltatime.h"
#include "src/fileio.h"
#include "src/filesystem/filemanager.h"
#include "src/input/input.h"
#include "src/thread/thread.h"
#include "src/thread/mythread.h"


// archt graphics
#include "src/gfx/opengl/camera.h"
#include "src/gfx/opengl/glmesh.h"
#include "src/gfx/opengl/glrenderapi.h"
#include "src/gfx/opengl/glrenderer2d.h"
#include "src/gfx/opengl/wireframerenderer.h"

#include "src/gfx/opengl/glshader.h"
#include "src/gfx/opengl/gltexture.h"
#include "src/gfx/opengl/glwindow.h"


// audio
#include "src/audio/openal/sounddevice.h"
#include "src/audio/openal/audiobuffer.h"
#include "src/audio/openal/audiosource.h"
#include "src/audio/openal/audiorenderer.h"

// gui
#include "src/gfx/gui/gui.h"

// math
#include "src/math/rayequation.h"

//imgui
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw.h"
#include "vendor/imgui/imgui_impl_opengl3.h"

//glm
#include <glm/gtx/transform.hpp>



// std
#include <math.h>

// pokememe
#include "pokemon.h"
#include "spritesheet.h"


// deletable
#include <ios>
#include <fstream>


double scrollTime = 10.0;
float scrollY = 0.0f;
float step = 0.0f;

bool debug = false;

int main() {

	using namespace archt;


	GLWindow* window = GLRenderAPI::init();
	GLRenderer2D::init();
	WireframeRenderer::init();

	Input::init();

#pragma region IMGUI_SETUP
	Gui::init(window);
	GLRenderAPI::createGuiInfoWindow();

	{
		glm::vec2 a1 = { -3.0f, 3.0f };
		glm::vec2 b1 = { 1.0f, 0.0f };

		glm::vec2 a2 = { -2.0f, 1.0f };
		glm::vec2 b2 = { 2.0f, 2.0f };

		glm::vec2 c = solveRayEquation(a1, b1, a2, b2);

		glm::vec2 v = b1 - a1;
		glm::vec2 w = b2 - a2;

		glm::vec2 p1 = a1 + c.x * v;
		glm::vec2 p2 = a2 + c.y * w;


		auto lambda = [&c, &p1, &p2]() {
			ImGui::Begin("Ray equation");
			ImGui::Text("t = %f", c.x);
			ImGui::Text("u = %f", c.y);

			ImGui::Text("p1 = %f\t %f", p1.x, p1.y);
			ImGui::Text("p2 = %f\t %f", p2.x, p2.y);



			ImGui::End();
		};
		Gui::instance->addGuiWindow(lambda);
	}


#pragma endregion IMGUI_SETUP


	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 1000.0f);


	//GLShader* shader = (GLShader*) FileManager::instance.loadFile("src/assets/shaders/shader/shader", FileManager::FileType::GL_SHADER_T);
	GLShader* fastShader = new GLShader("src/assets/shaders/fastshader/fastshader");
	GLShader* transferShader = new GLShader("src/assets/shaders/transfer/transfer");

	Uniformbuffer* uniformBuffer = new Uniformbuffer("matrices", nullptr, 4 * 16 * 1000);
	fastShader->registerUniformBuffer(uniformBuffer);
	transferShader->registerUniformBuffer(uniformBuffer);


	Pokemon pokemon;
	Pokemon pokemon1;

	SpriteSheet* trainerSheet = new SpriteSheet("src/assets/img/trainers.png");
	SpriteSheet* spriteSheet = new SpriteSheet("src/assets/img/pokememes.png");


	pokemon.setSpriteSheet(spriteSheet);
	pokemon.setShader(fastShader);
	pokemon1.setSpriteSheet(spriteSheet);
	pokemon1.setShader(fastShader);

#pragma region SOUND_SETUP
	SoundDevice::init();
	AudioRenderer::init();
	//AudioBuffer* music = new AudioBuffer("src/assets/audio/backgroundmusic/complete_osd_genII_custom.wav");
	AudioBuffer* music = new AudioBuffer("src/assets/audio/Pokemon Gold wave files/01 Pokemon GS Main Theme.wav");
	AudioBuffer* music1 = new AudioBuffer("src/assets/audio/backgroundmusic/title_screen.wav");
	AudioBuffer* music2 = new AudioBuffer("src/assets/audio/ak47-1.wav");

	AudioRenderer::setBackgroundMusic(music);
	AudioRenderer::playBackgroundMusic();

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
		pokemon1.setVbo(verteces, vSize);
		pokemon1.setIbo(indeces, iSize);


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
		pokemon1.setSpriteSize(spriteSize);
		pokemon1.setFootprintSize(spriteSheet->normalizeUv(footprintSize, footprintSize));

		glm::vec2 offsets[Pokemon::Sprite::NONE];
		offsets[Pokemon::Sprite::FRONT] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::FRONT_SHINY] = glm::vec2(0.0f, 0.0f);

		offsets[Pokemon::Sprite::FRONT_ALT] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::FRONT_ALT_SHINY] = glm::vec2(0.0f, 0.0f);


		offsets[Pokemon::Sprite::BACK] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::BACK_SHINY] = glm::vec2(0.0f, 0.0f);

		offsets[Pokemon::Sprite::FOOTPRINT] = glm::vec2(0.0f, 0.0f);

		pokemon.loadOffset("src/assets/img/pokememes_offset.txt");
		pokemon1.loadOffset("src/assets/img/pokememes_offset.txt");
	}

	pokemon.setUvs({ 0.0f, 0.0f });
	pokemon.setSprite(Pokemon::Sprite::FRONT);
	pokemon1.setUvs({ 0.0f, 0.0f });
	pokemon1.setSprite(Pokemon::Sprite::FRONT);

	pokemon1.translate({ 1.0f, 0.0f, 0.0f });

#pragma endregion UV_SETUP

	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);




	double elapsed = 0.0;
	double elapsed2 = 0.0;
	while (true) {



		DeltaTime::instance.update();

		double delta = DeltaTime::instance.getSeconds();
		elapsed += delta;
		elapsed2 += delta;
		//printf("elapsed : %f\n", elapsed);


		window->pollEvents();





#pragma region CONTROLS
		bool shift = Input::isPress(GLFW_KEY_LEFT_SHIFT) || Input::isHeld(GLFW_KEY_LEFT_SHIFT);
		bool control = Input::isPress(GLFW_KEY_LEFT_CONTROL) || Input::isHeld(GLFW_KEY_LEFT_CONTROL);
		float translation = 0.003f;
		if (control) {
			translation = 0.03f;
		}
		else if (shift) {
			translation = 0.3f;
		}


		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			//cam.translate({ 0.0f, 0.0f, -translation });
			pokemon.translate({ 0.0f, translation, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			//cam.translate({ 0.0f, 0.0f, translation });
			pokemon.translate({ 0.0f, -translation, 0.0f });
		}


		if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			pokemon.translate({ -translation, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			pokemon.translate({ translation, 0.0f, 0.0f });
		}

		if (Input::isPress(GLFW_KEY_E) || Input::isHeld(GLFW_KEY_E)) {
			cam.translate({ 0.0f, translation, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_F) || Input::isHeld(GLFW_KEY_F)) {
			cam.translate({ 0.0f, -translation, 0.0f });
		}


		static bool debugLock = false;
		if (Input::isPress(GLFW_KEY_G) || Input::isHeld(GLFW_KEY_G) && !debugLock) {
			debug = !debug;
			debugLock = true;
		}
		else if (Input::isPress(GLFW_KEY_G) || Input::isHeld(GLFW_KEY_G) && debugLock) {
			debugLock = false;
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

		if (pokemon.checkCollision(pokemon1, cam)) {
			printf("Collision\n");
		}


		//GLRenderAPI::setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//#if 1
		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);
		
		GLRenderer2D::submit(&pokemon);
		GLRenderer2D::submit(&pokemon1);
		
		
		GLRenderer2D::render();
		GLRenderer2D::flush();
		GLRenderer2D::endScene();
//#else
		WireframeRenderer::clear();
		WireframeRenderer::beginScene(&cam);
		
		WireframeRenderer::submit(&pokemon);
		WireframeRenderer::submit(&pokemon1);
		
		
		WireframeRenderer::render();
		WireframeRenderer::flush();
		WireframeRenderer::endScene();
//#endif

		AudioRenderer::render();

		//static bool transition = false;
		//if (elapsed2 > 10.0 && !transition) {
		//	AudioRenderer::fadeBackgroundMusic(music1, true, 5.0);
		//	transition = true;
		//}

#pragma region IMGUI

		Gui::instance->render();

#pragma endregion IMGUI


		window->swapBuffer();

		if (window->shouldClose()) {
			break;
		}
	}



	//ImGui_ImplGlfw_Shutdown();
	//ImGui_ImplOpenGL3_Shutdown();

	Gui::terminate();
	AudioRenderer::terminate();
	SoundDevice::terminate();
	WireframeRenderer::terminate();
	GLRenderer2D::terminate();
	GLRenderAPI::terminate();
	FileManager::instance.deleteAllFiles();

	return 0;
}

#else {

#include "src/core.h"

#include "src/gfx/render/renderer.h"

int main() {
	using namespace archt;

	GLWindow* window = GLRenderAPI::init();



	Gui::init(window);
	GLRenderAPI::createGuiInfoWindow();

	Renderer::createInstance();
	Renderer::instance->setRenderSettings();
	//Renderer2D::createInstance();

	Input::init();

	ptr<Camera_new> camera = make_ptr<Camera_new>( 60.0f, 1080.0f / 720.0f, 0.001f, 100.0f);

	ptr<Entity> entity = make_ptr<Entity>();
	ptr<Entity> entity1 = make_ptr<Entity>();


#pragma region SETUP
	{

		float u = 1.0f / 1711;
		float v = 18.0f / 5609;
		float sizeX = 56.0f / 1711;
		float sizeY = 56.0f / 5609;

		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize]{
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { u, v}, 0.0f, 0.0f),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { u + sizeX, v}, 0.0f, 0.0f),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { u + sizeX, v + sizeY}, 0.0f, 0.0f),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { u, v + sizeY}, 0.0f, 0.0f)
		};




		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize]{
			0, 1, 2,
			0, 2, 3
		};

		ptr<Mesh> mesh = make_ptr<Mesh>();
		ptr<Mesh> mesh1 = make_ptr<Mesh>();

		mesh->setVBO(verteces, vSize);
		mesh->setIBO(indeces, iSize);

		mesh1->setVBO(verteces, vSize);
		mesh1->setIBO(indeces, iSize);




		//#define SIMPLE_RENDERER
#ifdef SIMPLE_RENDERER
		ptr<Material> material = make_ptr<Material>("src/assets/shaders/testshader/testshader", "src/assets/img/item.png");
#else
		ptr<Material> material = make_ptr<Material>("src/assets/shaders/fastshader/fastshader", "src/assets/img/pokememes.png");
		Uniformbuffer* uniformBuffer = new Uniformbuffer("matrices", nullptr, 4 * 16 * 1000);
		material->getShader().registerUniformBuffer(uniformBuffer);
#endif


		mesh->addComponent(material);
		mesh1->addComponent(material);
		mesh1->createGuiWindow(camera);

		entity->addComponent(mesh);

		mesh1->translate({ 0.3f, 0.3f, 0.0f });
		entity1->addComponent(mesh1);
		
	}

#pragma endregion SETUP



	


	while (true) {


	

		window->pollEvents();
#pragma region CONTROLS

		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			camera->translate({ 0.0f, 0.0f, 0.003f});
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			camera->translate({ 0.0f, 0.0f, -0.003f});
		}

		if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			//camera->translate({ 0.003f, 0.0f, 0.0f });
			entity1->getComponent<Mesh>()->translate({ 0.03f, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			//camera->translate({ -0.003f, 0.0f, 0.0f });
			entity1->getComponent<Mesh>()->translate({ -0.03f, 0.0f, 0.0f });
		}

#pragma endregion CONTROLS



#ifdef SIMPLE_RENDERER
		Renderer::instance->clear();
		Renderer::instance->render(entity, camera);
#else
		Renderer::instance->clear();
		Renderer::instance->beginScene(camera);
		
		Renderer::instance->submit(entity);
		Renderer::instance->submit(entity1);


		Renderer::instance->render();
		Renderer::instance->endScene();
		Renderer::instance->flush();
#endif


		//Renderer2D::instance->clear();
		//Renderer2D::instance->beginScene(camera);
		//
		//Renderer2D::instance->submit(entity);
		//
		//Renderer2D::instance->render();
		//Renderer2D::instance->endScene();
		//Renderer2D::instance->flush();

		Gui::instance->render();

		window->swapBuffer();

		if (window->shouldClose()) {
			break;
		}
	}

	delete window;

	Input::terminate();

	Gui::terminate();

	Renderer::deleteInstance();

	Renderer2D::deleteInstance();
	
	GLRenderAPI::terminate();


	return 0;
}




#endif