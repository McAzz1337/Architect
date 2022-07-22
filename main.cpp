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



int main() {

	using namespace archt;


	GLWindow* window = GLRenderAPI::init();
	GLRenderer2D::init();
	Input::init();

	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 1000.0f);


	GLShader* shader = (GLShader*) FileManager::instance.loadFile("src/assets/shaders/shader", FileManager::FileType::GL_SHADER_T);

	int meshSize = 100 * 100;// GLRenderAPI::getMaxMatricesCount();
	GLMesh* meshes = new GLMesh[meshSize];
	GLTexture* tex;
	GLTexture* tex2;

	{
		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize]{
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }, 0, 0),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 0, 0),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }, 0, 0),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f }, 0, 0)
		};

		


		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize]{
			0, 1, 2,
			0, 2, 3
		};

		uint32_t* indeces2 = new uint32_t[iSize];
		memcpy_s(indeces2, iSize * sizeof(uint32_t), indeces, iSize * sizeof(uint32_t));



		tex = (archt::GLTexture*) FileManager::instance.loadFile("src/assets/img/item.png", FileManager::FileType::GL_TEXTURE_T);
		tex2 = (archt::GLTexture*) FileManager::instance.loadFile("src/assets/img/item2.png", FileManager::FileType::GL_TEXTURE_T);

		//mesh.setTexture(tex);
		//mesh2.setTexture(tex2);

		for (int i = 0; i < meshSize; i++) {

			meshes[i].setVbo(verteces, vSize);
			meshes[i].setIbo(indeces, iSize);



			meshes[i].setShader(shader);
		}
	}



	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			int index = y * 100 + x;
			meshes[index].translate({ (float) x, (float) y, 0.0f });
			if (y & 0b1) { 
				if (index & 0b1)	meshes[index].setTexture(tex);
				else				meshes[index].setTexture(tex2); 
			}
			else {
				if (index & 0b1)	meshes[index].setTexture(tex2);
				else				meshes[index].setTexture(tex);
			}
		}
	}


	

	

	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);




	while (true) {

		window->pollEvents();

		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			cam.translate({ 0.0f, 0.0f, -0.3f });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			cam.translate({ 0.0f, 0.0f, 0.3f });

		}


		if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			cam.translate({ -0.3f, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			cam.translate({ 0.3f, 0.0f, 0.0f });
		}

		if (Input::isPress(GLFW_KEY_E) || Input::isHeld(GLFW_KEY_E)) {
			cam.translate({ 0.0f, 0.3f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_F) || Input::isHeld(GLFW_KEY_F)) {
			cam.translate({ 0.0f, -0.3f, 0.0f });
		}


		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);

		

		for (int i = 0; i < meshSize; i++) {
			GLRenderer2D::submit(&meshes[i]);
		}


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