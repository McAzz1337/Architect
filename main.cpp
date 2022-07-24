#include <iostream>
#include "src/gfx/opengl/glrenderapi.h"
#include "src/gfx/opengl/glrenderer2d.h"
#include "src/gfx/opengl/glwindow.h"
#include "src/gfx/opengl/gltexture.h"

#include "src/gfx/opengl/camera.h"
#include "src/gfx/opengl/glshader.h"
#include "src/gfx/opengl/glmesh.h"


#include "src/input/input.h"

#include "src/fileio.h"
#include "src/filesystem/filemanager.h"

#include <glm/gtx/transform.hpp>

#include "src/thread.h"

#include <math.h>



#include "pokemon.h"


int main() {

	using namespace archt;


	GLWindow* window = GLRenderAPI::init();
	GLRenderer2D::init();
	Input::init();

	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 1000.0f);


	GLShader* shader = (GLShader*) FileManager::instance.loadFile("src/assets/shaders/shader/shader", FileManager::FileType::GL_SHADER_T);
	GLShader* fastShader = (GLShader*) FileManager::instance.loadFile("src/assets/shaders/fastshader/fastshader", FileManager::FileType::GL_SHADER_T);
	Uniformbuffer* uniformBuffer = new Uniformbuffer(nullptr, 4 * 16 * 1000);
	fastShader->registerUniformBuffer(uniformBuffer);

	int meshSize = 251;// GLRenderAPI::getMaxMatricesCount();
	GLMesh* meshes = new GLMesh[meshSize];
	GLMesh mesh;
	GLTexture* tex;
	GLTexture* tex2;
	GLTexture* sprites;
	Pokemon pokemon;

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

		mesh.setVbo(verteces, vSize);
		mesh.setIbo(indeces, iSize);
		pokemon.setVbo(verteces, vSize);
		pokemon.setIbo(indeces, iSize);



		tex = (GLTexture*) FileManager::instance.loadFile("src/assets/img/item.png", FileManager::FileType::GL_TEXTURE_T);
		tex2 = (GLTexture*) FileManager::instance.loadFile("src/assets/img/item2.png", FileManager::FileType::GL_TEXTURE_T);
		sprites = (GLTexture*) FileManager::instance.loadFile("src/assets/img/pokememes.png", FileManager::FileType::GL_TEXTURE_T);
		mesh.setTexture(sprites);
		pokemon.setTexture(sprites);

		//mesh2.setTexture(tex2);

		for (int i = 0; i < meshSize; i++) {

			meshes[i].setVbo(verteces, vSize);
			meshes[i].setIbo(indeces, iSize);

			meshes[i].setShader(fastShader);
		}
		mesh.setShader(fastShader);
		pokemon.setShader(fastShader);

	}


	Pokemon::setSpriteSheetSize(glm::vec2(1711.0f, 5609.0f));
	const glm::vec2& spriteSheetSize = Pokemon::getSpriteSheetSize();
	int spriteSize = 56;
	int infoHeight = 18;
	int strideY = 188;
	int strideX = 171;


	glm::vec2 uvs[251];
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 10; j++) {
			int index = i * 10 + j;
			if (index == meshSize) {
				goto BREAK;
			}
			int yPos = i * strideY + infoHeight;
			int xPos = j * strideX + 1;

			float x = (float) xPos / spriteSheetSize.x;
			float y = (float) yPos / spriteSheetSize.y;

			uvs[index] = glm::vec2(x, y);
			printf("uvs[%i] = %f %f\n", index, x, y);
		}
	}
BREAK:

	float sx = (float) spriteSize / spriteSheetSize.x;
	float sy = (float) spriteSize / spriteSheetSize.y;
	for (int y = 0; y < 26; y++) {
		for (int x = 0; x < 10; x++) {
			int index = y * 10 + x;
			if (index == meshSize) {
				goto BREAK2;
			}
			VBO* vbo = meshes[index].getVBO();
			Vertex* data = vbo->getData();
			data[0].uv = uvs[index];
			data[1].uv = uvs[index] + glm::vec2(sx, 0);
			data[2].uv = uvs[index] + glm::vec2(sx, sy);
			data[3].uv = uvs[index] + glm::vec2(0, sy);


			meshes[index].translate({ (float) x, (float) y, 0.0f });
			meshes[index].setTexture(sprites);


			//if (y & 0b1) {
			//	if (index & 0b1)	meshes[index].setTexture(tex);
			//	else				meshes[index].setTexture(tex2); 
			//}
			//else {
			//	if (index & 0b1)	meshes[index].setTexture(tex2);
			//	else				meshes[index].setTexture(tex);
			//}

		}
	}
BREAK2:

	{
		Pokemon::setSpriteSize({ sx, sy });
		glm::vec2 offsets[Pokemon::Sprite::NONE];
		offsets[Pokemon::Sprite::FRONT] = glm::vec2(0.0f, 0.0f);
		offsets[Pokemon::Sprite::FRONT_SHINY] = glm::vec2(sx + 1.0f / spriteSheetSize.x, 0.0f);

		offsets[Pokemon::Sprite::FRONT_ALT] = glm::vec2(0.0f, sy + 1.0f / spriteSheetSize.y);
		offsets[Pokemon::Sprite::FRONT_ALT_SHINY] = glm::vec2(sx + 1.0f / spriteSheetSize.x, sy + 1.0f / spriteSheetSize.y);


		offsets[Pokemon::Sprite::BACK] = glm::vec2(0.0f, sy * 2.0f + 2.0f / spriteSheetSize.y);
		offsets[Pokemon::Sprite::BACK_SHINY] = glm::vec2(sx + 1.0f / spriteSheetSize.x, sy * 2.0f + 2.0f / spriteSheetSize.y);
		Pokemon::setUVOffsets(offsets);
	}
	pokemon.setUvs({ 1.0f / spriteSheetSize.x, (float) infoHeight / spriteSheetSize.y });
	pokemon.setSprite(Pokemon::Sprite::BACK);


	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);




	while (true) {

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



		float dx = sx / 20.0f;
		float dy = sy / 20.0f;
		if (control) {
			dx = 0.1f / spriteSheetSize.x;
			dy = 0.1f / spriteSheetSize.y;
		}
		else if (shift) {
			dx = sx / 60.0f;
			dy = sy / 60.0f;
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
			//cam.rotate({ 0.0f, -1.0f, 0.0f }, M_PI / 36.0f);
		}
		else if (Input::isPress(GLFW_KEY_LEFT) || Input::isHeld(GLFW_KEY_LEFT)) {
			pokemon.translateUv(glm::vec2(-dx, 0.0f));
			//cam.rotate({ 0.0f, 1.0f, 0.0f }, M_PI / 36.0f);
		}

		if (Input::isPress(GLFW_KEY_UP) || Input::isHeld(GLFW_KEY_UP)) {
			pokemon.translateUv(glm::vec2(0.0f, -dy));
			//cam.rotate({ 0.0f, -1.0f, 0.0f }, M_PI / 36.0f);
		}
		else if (Input::isPress(GLFW_KEY_DOWN) || Input::isHeld(GLFW_KEY_DOWN)) {
			pokemon.translateUv(glm::vec2(0.0f, dy));
			//cam.rotate({ 0.0f, 1.0f, 0.0f }, M_PI / 36.0f);
		}
#pragma endregion CONTROLS
		/*
		for (int y = 0; y < 100; y++) {
			for (int x = 0; x < 100; x++) {
				int index = y * 100 + x;
				if (y & 0b1) {
					if (index & 0b1)	meshes[index].rotate(M_PI / 36.0f, { 0.0f, 1.0f, 0.0f });
					else				meshes[index].rotate(M_PI / 36.0f, { 0.0f, -1.0f, 0.0f });
				}
				else {
					if (index & 0b1)	meshes[index].rotate(M_PI / 36.0f, { 0.0f, -1.0f, 0.0f });
					else				meshes[index].rotate(M_PI / 36.0f, { 0.0f, 1.0f, 0.0f });
				}
			}
		}
		*/

		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);



		for (int i = 0; i < meshSize; i++) {
			GLRenderer2D::submit(&meshes[i]);
		}
		//GLRenderer2D::submit(&mesh);
		//GLRenderer2D::submit(&pokemon);


		GLRenderer2D::render();
		GLRenderer2D::flush();
		GLRenderer2D::endScene();


		window->swapBuffer();

		if (window->shouldClose()) {
			break;
		}
	}

	GLRenderer2D::terminate();
	FileManager::instance.deleteAllFiles();

	return 0;
}