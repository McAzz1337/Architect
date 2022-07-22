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

	GLMesh mesh;
	GLMesh mesh2;
	int meshSize = 1000;// GLRenderAPI::getMaxMatricesCount();
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

		Vertex* verteces2 = new Vertex[vSize]{
			Vertex({ -0.3f,  0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }, 0, 0),
			Vertex({  0.3f,  0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 0, 0),
			Vertex({  0.3f, -0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }, 0, 0),
			Vertex({ -0.3f, -0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f }, 0, 0)
		};



		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize]{
			0, 1, 2,
			0, 2, 3
		};

		uint32_t* indeces2 = new uint32_t[iSize];
		memcpy_s(indeces2, iSize * sizeof(uint32_t), indeces, iSize * sizeof(uint32_t));

		mesh.setVbo(verteces, vSize);
		mesh.setIbo(indeces, iSize);


		mesh2.setVbo(verteces2, vSize);
		mesh2.setIbo(indeces2, iSize);


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



	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 50; x++) {
			int index = y * 50 + x;
			meshes[index].translate({ (float) x, (float) y, 0.0f });
			if (index & 0b1)	meshes[index].setTexture(tex2);
			else			meshes[index].setTexture(tex);
		}
	}


	mesh.setShader(shader);
	mesh2.setShader(shader);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model2 = glm::mat4(1.0f);

	model = glm::translate(model, { -0.5005f, 0.0f, 0.0f });

	mesh.setModelMatrix(model);
	mesh2.setModelMatrix(model2);

	FileManager::instance.logAllocateMemory(FileManager::DataType::KILO_BYTES);




	while (true) {

		window->pollEvents();

		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			cam.translate({ 0.0f, 0.0f, 0.3f });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			cam.translate({ 0.0f, 0.0f, -0.3f });

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

		if (Input::isPress(GLFW_KEY_J) || Input::isHeld(GLFW_KEY_J)) {
			for (int i = 0; i < 100; i++) {
				meshes[i].translate({ -0.3f, 0.0f, 0.0f });
			}
		}
		else if (Input::isPress(GLFW_KEY_L) || Input::isHeld(GLFW_KEY_L)) {
			for (int i = 0; i < 100; i++) {
				meshes[i].translate({ 0.3f, 0.0f, 0.0f });
			}
		}

		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);

		//GLRenderer2D::submit(&mesh);
		//GLRenderer2D::submit(&mesh2);

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