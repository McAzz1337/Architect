#include "renderer.h"

#include "../opengl/glrenderapi.h"

#include "../../entity/component/mesh.h"
#include "../../entity/component/material/material.h"
#include "../../entity/component/transform.h"

namespace archt {

	Renderer::Renderer() {
		
		GLRenderAPI::enable(GL_BLEND);
		GLRenderAPI::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	}

	Renderer::~Renderer() {}

	void Renderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::render(ptr<Entity> entity, ptr<Camera_new> cam) {
		VBO* vbo = entity->getComponent<Mesh>()->getVBO();
		IBO* ibo = entity->getComponent<Mesh>()->getIBO();

		vao = new GLVertexarray(vbo, ibo);
	
		GLShader* shader = &entity->getComponent<Mesh>()->getComponent<Material>()->getShader();
		shader->bind();
		vbo->bind();
		ibo->bind();
		vao->bind();

		Transform mvp = (cam->getProjectionView()) * (*(entity->getComponent<Mesh>()->getTransform()));

		shader->setMat4("mvp", mvp.getMatrix());

		glDrawElements(GL_TRIANGLES, ibo->getSize(), GL_UNSIGNED_INT, nullptr);
	}

}