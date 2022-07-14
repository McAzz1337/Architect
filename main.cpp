#include <iostream>
#include "src/gfx/opengl/glrenderer2d.h"
#include "src/gfx/opengl/glwindow.h"

#include "src/gfx/opengl/camera.h"
#include "src/gfx/opengl/glshader.h"
#include "src/gfx/opengl/glmesh.h"

#include "src/input/input.h"

#include "src/fileio.h"

#include <glm/gtx/transform.hpp>

#include <math.h>

int main() {

	using namespace archt;
	
	GLWindow window("Architect", 0, 0, 1080, 720);
	GLRenderer2D::init();
	Input::init();

	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.01f, 1000.0f);

	GLMesh mesh;
	{
		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize] {
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f })
		};
	

		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize] {
			0, 1, 2,
			0, 2, 3
		};


		mesh.setVbo(verteces, vSize);
		mesh.setIbo(indeces, iSize);
	}
	

	GLShader shader("src/assets/shaders/shader");
	shader.bind();

	glm::mat4 model = glm::mat4(1.0f);



	while (true) {

		window.pollEvents();
		
		if (Input::isPress(GLFW_KEY_W)) {
			model = glm::translate(model, { 0.0f, 0.01f, 0.0f });
			printf("pressed w\n");
		}
		else if (Input::isPress(GLFW_KEY_S)) {
			model = glm::translate(model, { 0.0f, -0.01f, 0.0f });
			printf("pressed s\n");
		}
		else if (Input::isHeld(GLFW_KEY_W)) {
			model = glm::translate(model, { 0.0f, 0.01f, 0.0f });
			printf("held w\n");
		}
		else if (Input::isHeld(GLFW_KEY_S)) {
			model = glm::translate(model, { 0.0f, -0.01f, 0.0f });
			printf("held s\n");
		}

	
	
		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);

		GLRenderer2D::submit(mesh.getVBO(), mesh.getIBO());

		glm::mat4 mvp = cam.getProjectionView() * model;
		shader.setMat4("mvp", mvp);
		GLRenderer2D::render();
		GLRenderer2D::flush();
		GLRenderer2D::endScene();


		window.swapBuffer();
		
		if (window.shouldClose()) {
			break;
		}
	}


	return 0;
}