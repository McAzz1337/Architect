#include <iostream>


#include "src/core.h"

#include "src/gfx/render/renderer.h"

#include <entt/entt.hpp>

//#define OLD_CODE
#ifdef OLD_CODE

float speed = 0.03f;
float fastSpeed = 0.08f;
float lowSPeed = 0.004;


//#define SIMPLE_RENDERER

float speeds[3] = { 0.002f, 0.02f, 0.05f };

void controlSpeeds() {

	ImGui::Begin("Camera speed");

	ImGui::SliderFloat("CTRL", &speeds[0], 0.001f, 0.01f);
	ImGui::SliderFloat("DEFAULT", &speeds[1], 0.01f, 0.04f);
	ImGui::SliderFloat("SHIFT", &speeds[2], 0.04f, 0.08f);

	ImGui::End();
}


int main() {

	using namespace archt;

	GLWindow* window = GLRenderAPI::init();



	Gui::init(window);
	Gui::instance->addGuiWindow([] { ImGui::ShowDemoWindow(); });
	system_info::createSysteminfoWindow();
	GLRenderAPI::createGuiInfoWindow();

	Renderer::createInstance();
	Renderer::instance->setRenderSettings();

	Framebuffer* fb = new Framebuffer(window->getSize());
	Framebuffer* fb2 = new Framebuffer(window->getSize());


	Input::init();

	Scene scene;
	Entity_s e = scene.createEntity();
	scene.addComponent<Transform_s>(e);

	ptr<Camera_new> camera = make_ptr<Camera_new>(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 100.0f);

	ptr<Camera_new> camera1 = make_ptr<Camera_new>(M_PI / 3.0f, 1080.0f / 720.0f, 0.001f, 100.0f);
	camera1->translate({ 1.0f, 0.0f, -1.0f });
	camera1->rotate((M_PI / 4.0f), { 0.0f, 1.0f, 0.0f });


	ptr<Entity> entity = make_ptr<Entity>();
	ptr<Entity> entity1 = make_ptr<Entity>();


#pragma region SETUP
	{

		float u = 1.0f / 1711.0f;
		float v = 18.0f / 5609.0f;
		float sizeX = 56.0f / 1711.0f;
		float sizeY = 56.0f / 5609.0f;

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
		ptr<Mesh> cameraMesh = make_ptr<Mesh>();



		mesh->setVBO(verteces, vSize);
		mesh->setIBO(indeces, iSize);

		mesh1->setVBO(verteces, vSize);
		mesh1->setIBO(indeces, iSize);

		verteces[0].uv = glm::vec2(0.0f, 0.0f);
		verteces[1].uv = glm::vec2(1.0f, 0.0f);
		verteces[2].uv = glm::vec2(1.0f, 1.0f);
		verteces[3].uv = glm::vec2(0.0f, 1.0f);

		cameraMesh->setVBO(verteces, vSize);
		cameraMesh->setIBO(indeces, iSize);




		ptr<Material> material = make_ptr<Material>("src/assets/shaders/fastshader/fastshader", "src/assets/img/pokememes.png");
		Uniformbuffer* uniformBuffer = new Uniformbuffer("matrices", nullptr, 4 * 16 * 1000);
		material->getShader().registerUniformBuffer(uniformBuffer);

		ptr<Material> cameraMaterial = make_ptr<Material>("src/assets/shaders/fastshader/fastshader", "src/assets/img/camera.png");
		cameraMaterial->getShader().registerUniformBuffer(uniformBuffer);

		mesh->addComponent(material);
		mesh1->addComponent(material);
		cameraMesh->addComponent(cameraMaterial);

		//mesh1->createGuiWindow(camera);

		entity->addComponent(mesh);

		mesh1->translate({ 0.3f, 0.3f, 0.0f });
		entity1->addComponent(mesh1);

		camera->addComponent<Mesh>(cameraMesh);


	}

#pragma endregion SETUP






	while (true) {


		window->pollEvents();

#pragma region CONTROLS


		Gui::instance->submitWIndow(controlSpeeds);

		float speed = speeds[1];

		if (Input::isPress(GLFW_KEY_LEFT_SHIFT) || Input::isHeld(GLFW_KEY_LEFT_SHIFT)) {
			speed = speeds[2];
		}
		else if (Input::isRelease(GLFW_KEY_LEFT_SHIFT)) {
			speed = speeds[1];
		}
		if (Input::isPress(GLFW_KEY_LEFT_CONTROL) || Input::isHeld(GLFW_KEY_LEFT_CONTROL)) {
			speed = speeds[0];
		}
		else if (Input::isRelease(GLFW_KEY_LEFT_CONTROL)) {
			speed = speeds[1];
		}



		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			camera->translate({ 0.0f, 0.0f, speed });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			camera->translate({ 0.0f, 0.0f, -speed });
		}

		if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			//camera->translate({ 0.003f, 0.0f, 0.0f });
			entity1->getComponent<Mesh>()->translate({ speed, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			//camera->translate({ -0.003f, 0.0f, 0.0f });
			entity1->getComponent<Mesh>()->translate({ -speed, 0.0f, 0.0f });
		}

#pragma endregion CONTROLS


		if (entity->getComponent<Mesh>()->checkCollision(entity1->getComponent<Mesh>(), camera)) {
			printf("collision\n");
		}


		{
			const glm::vec3& camPos = camera->getPosition();
			const glm::vec3 camDir = { 0.0f, 0.0f, 1.0f };
			const glm::vec3& camPos1 = camera1->getPosition();

			float angle = getAngle(camPos, camPos + camDir, camPos1);

			auto lambda = [angle]() {
				ImGui::Begin("Angle");
				ImGui::Text("Angle: \t%f", angle);
				ImGui::End();

			};
			//Gui::instance->submitWIndow(lambda);


		}


		Renderer::instance->setRendertarget(fb);
		Renderer::instance->clear();
		Renderer::instance->beginScene(camera);

		Renderer::instance->submit(entity);
		Renderer::instance->submit(entity1);


		Renderer::instance->render();
		Renderer::instance->endScene();
		Renderer::instance->flush();





		Renderer::instance->setRendertarget(fb2);
		Renderer::instance->clear();
		Renderer::instance->beginScene(camera1);

		Renderer::instance->submit(camera);
		Renderer::instance->submit(entity);
		Renderer::instance->submit(entity1);


		Renderer::instance->render();
		Renderer::instance->endScene();
		Renderer::instance->flush();




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


#else


int main() {
	using namespace archt;

	GLWindow* window = GLRenderAPI::init();

	Input::init();
	Gui::init(window);

	Renderer::createInstance();

	Scene scene;
#pragma region ENTITY_SETUP
	Entity_s entity = scene.createEntity();
	entity.addComponent<Transform_s>();

	{
		float u = 1.0f / 1711.0f;
		float v = 18.0f / 5609.0f;
		float sizeX = 56.0f / 1711.0f;
		float sizeY = 56.0f / 5609.0f;

		uint32_t vSize = 4;
		Vertex* verteces = new Vertex[vSize]{
			Vertex({ -0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f}, 0.0f, 0.0f),
			Vertex({  0.5f,  0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 0.0f}, 0.0f, 0.0f),
			Vertex({  0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f}, 0.0f, 0.0f),
			Vertex({ -0.5f, -0.5f, 0.0f }, {0.0f, 0.0f, 0.0f}, { 0.0f, 1.0f}, 0.0f, 0.0f)
		};


		uint32_t iSize = 6;
		uint32_t* indeces = new uint32_t[iSize]{
			0, 1, 2,
			0, 2, 3
		};

		entity.addComponent<Mesh_s>(verteces, vSize, indeces, iSize);

		entity.addComponent<Material_s>(std::string("src/assets/img/item.png"),
										std::string(""),
										std::string("src/assets/shaders/fastshader/fastshader"));
	}



#pragma endregion ENTITY_SETUP


	SceneRenderer::createInstance();
	SceneRenderer::instance->setRenderSettings();

	ptr<Camera_new> cam;
	{
		glm::ivec2 windowSize = window->getSize();
		cam = make_ptr<Camera_new>(M_PI / 3.0f, windowSize.x / windowSize.y, 0.01f, 100.0f);
	}

	{

		auto lambda = [&entity, &cam]() {

			ImGui::Begin("Entity");

			if (entity.hasComponent<Transform_s>()) {

				glm::mat4& m = entity.getComponent<Transform_s>();
				ImGui::Text("Transform");
				for (int i = 0; i < 4; i++) {
					ImGui::Text("%f\t%f\t%f\t%f", m[i][0], m[i][1], m[i][2], m[i][3]);
				}

				ImGui::Separator();

				ImGui::Text("MVP");
				glm::mat4 n = cam->getProjectionView().getMatrix() * entity.getComponent<Transform_s>().transform;
				for (int i = 0; i < 4; i++) {
					ImGui::Text("%f\t%f\t%f\t%f", n[i][0], n[i][1], n[i][2], n[i][3]);
				}

				ImGui::Separator();
				
			}
			if (entity.hasComponent<Mesh_s>()) {

				Mesh_s& mesh = entity.getComponent<Mesh_s>();

				VBO& vbo = mesh.vbo;
				Vertex* verteces = vbo.getData();

				ImGui::Text("Vertex buffer");
				for (int i = 0; i < vbo.getSize(); i++) {
					Vertex& v = verteces[i];
					ImGui::Text("%f\t%f\t%f", v.pos.x, v.pos.y, v.pos.z);
				}

				IBO& ibo = mesh.ibo;
				uint32_t* indeces = ibo.getData();

				ImGui::Text("Index buffer");
				for (int i = 0; i < ibo.getSize(); i++) {
					ImGui::Text("%i", indeces[i]);
				}

				ImGui::Separator();
			}
			if (entity.hasComponent<Material_s>()) {

				ImGui::Text("Material");

				Material_s& mat = entity.getComponent<Material_s>();
				glm::vec2 s = mat.tex->getSize();
				ImVec2 size = { s.x, s.y };
				ImGui::Image((ImTextureID) mat.tex->getId(), { 256, 256 });

				ImGui::Separator();
			}
			ImGui::End();

		};
		Gui::instance->addGuiWindow(lambda);
	}


	Framebuffer fb(window->getSize());


	while (true) {

		window->pollEvents();


		if (Input::isPress(GLFW_KEY_W) || Input::isHeld(GLFW_KEY_W)) {
			cam->translate({ 0.0f, 0.0f, 0.03f });
		}
		else if (Input::isPress(GLFW_KEY_S) || Input::isHeld(GLFW_KEY_S)) {
			cam->translate({ 0.0f, 0.0f, -0.03f });
		}
		if (Input::isPress(GLFW_KEY_A) || Input::isHeld(GLFW_KEY_A)) {
			cam->translate({ -0.03f, 0.0f, 0.0f });
		}
		else if (Input::isPress(GLFW_KEY_D) || Input::isHeld(GLFW_KEY_D)) {
			cam->translate({ 0.03f, 0.0f, 0.0f });
		}

		SceneRenderer::instance->setRendertarget(&fb);

		//Transform_s& t = entity.getComponent<Transform_s>();
		//t.rotate(M_PI / 60.0f, { 0.0f, 1.0f, 0.0f });

		SceneRenderer::instance->clear();
		SceneRenderer::instance->beginScene(&scene, cam);

		SceneRenderer::instance->submit(entity);

		SceneRenderer::instance->render();

		SceneRenderer::instance->endScene();
		SceneRenderer::instance->flush();


		Gui::instance->render();


		window->swapBuffer();

		if (window->shouldClose()) {
			break;
		}
	}

	SceneRenderer::deleteInstance();


	delete window;

	Renderer::deleteInstance();
	Gui::terminate();
	Input::terminate();
	GLRenderAPI::terminate();

	return 0;
}



#endif

