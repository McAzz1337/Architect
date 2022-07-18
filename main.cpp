#include <iostream>
#include "src/gfx/opengl/glrenderapi.h"
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
	GLRenderAPI::init();
	GLRenderer2D::init();
	Input::init();

	Camera cam(M_PI / 3.0f, 1080.0f / 720.0f, 0.01f, 1000.0f);

	GLMesh mesh;
	GLMesh mesh2;
	{
		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize] {
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }, 0),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 0),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }, 0),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f }, 0)
		};

		Vertex* verteces2 = new Vertex[vSize] {
			Vertex({ -0.3f,  0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f }, 0),
			Vertex({  0.3f,  0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f }, 0),
			Vertex({  0.3f, -0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f }, 0),
			Vertex({ -0.3f, -0.3f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f }, 0)
		};
		
	

		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize] {
			0, 1, 2,
			0, 2, 3
		};

		uint32_t* indeces2 = new uint32_t[iSize];
		memcpy_s(indeces2, iSize * sizeof(uint32_t), indeces, iSize * sizeof(uint32_t));

		mesh.setVbo(verteces, vSize);
		mesh.setIbo(indeces, iSize);


		mesh2.setVbo(verteces2, vSize);
		mesh2.setIbo(indeces2, iSize);
		
		GLTexture* tex = new GLTexture("src/assets/img/item.png");
		GLTexture* tex2 = new GLTexture("src/assets/img/item2.png");


		mesh.setTexture(tex);
		mesh2.setTexture(tex2);
	}
	

	GLShader shader("src/assets/shaders/shader");
	mesh.setShader(&shader);
	mesh2.setShader(&shader);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 model2 = glm::mat4(1.0f);

	model = glm::translate(model, { -0.5005f, 0.0f, 0.0f });


	while (true) {

		window.pollEvents();
		
		if (Input::isPress(GLFW_KEY_W)) {
			model = glm::translate(model, { 0.0f, 0.01f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_S)) {
			model = glm::translate(model, { 0.0f, -0.01f, 0.0f });
		}
		else if (Input::isHeld(GLFW_KEY_W)) {
			model = glm::translate(model, { 0.0f, 0.01f, 0.0f });
		}
		else if (Input::isHeld(GLFW_KEY_S)) {
			model = glm::translate(model, { 0.0f, -0.01f, 0.0f });
		}

		if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			model = glm::rotate(model, (float) -(M_PI / 180.0f), {0.0f, 1.0f, 0.0f});
		}
		else if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			model = glm::rotate(model, (float) M_PI / 180.0f, { 0.0f, 1.0f, 0.0f });
		}

	
		GLRenderer2D::clear();
		GLRenderer2D::beginScene(&cam);

		GLRenderer2D::submit(&mesh);
		GLRenderer2D::submit(&mesh2);

		glm::mat4 mvp = cam.getProjectionView() * model;
		glm::mat4 mvp2 = cam.getProjectionView() * model2;

		shader.bind();
		shader.setMat4("mvp", mvp);
		shader.setMat4("mvp2", mvp2);
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