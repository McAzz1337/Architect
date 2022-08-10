#include "glmesh.h"

#include "../../filesystem/filemanager.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../math/soe2.h"

#include "../gui/gui.h"

extern bool debug;

namespace archt {



	GLMesh::GLMesh() {
		Gui::instance->addGuiWindow([this]() {
			glm::mat4 m = this->getModelMatrix();
			ImGui::Begin("Pokemon");
			ImGui::Text("Matrix");
			ImGui::Text("%f\t%f\t%f\t%f", m[0][0], m[0][1], m[0][2], m[0][3]);
			ImGui::Text("%f\t%f\t%f\t%f", m[1][0], m[1][1], m[1][2], m[1][3]);
			ImGui::Text("%f\t%f\t%f\t%f", m[2][0], m[2][1], m[2][2], m[2][3]);
			ImGui::Text("%f\t%f\t%f\t%f", m[3][0], m[3][1], m[3][2], m[3][3]);


			ImGui::End();
									});
	}

	GLMesh::GLMesh(VBO* vbo, IBO* ibo) : vbo(vbo), ibo(ibo) {}

	GLMesh::GLMesh(VBO* vbo, IBO* ibo, const std::string& texture) : vbo(vbo), ibo(ibo) {

	}

	GLMesh::GLMesh(Vertex* verteces, uint32_t vSize, uint32_t* indeces, uint32_t iSize) {
		vbo = new VBO(verteces, vSize);
		ibo = new IBO(indeces, iSize);
	}


	GLMesh::~GLMesh() {
		if (vbo) delete vbo;
		if (ibo) delete ibo;
	}

	void GLMesh::translate(const glm::vec3& t) {
		modelMatrix = glm::translate(modelMatrix, t);
	}

	void GLMesh::rotate(float angle, const glm::vec3& axis) {
		modelMatrix = glm::rotate(modelMatrix, angle, axis);

	}

	void GLMesh::scale(const glm::vec3& s) {
		modelMatrix = glm::scale(modelMatrix, s);
	}

	void GLMesh::resetMatrix() {
		modelMatrix = glm::mat4(1.0f);
	}


	void GLMesh::setVbo(VBO* vbo) {
		if (this->vbo)
			delete this->vbo;

		this->vbo = vbo;
	}

	void GLMesh::setVbo(Vertex* verteces, uint32_t size) {
		if (vbo)
			delete vbo;

		vbo = new VBO(verteces, size);
	}

	void GLMesh::setIbo(IBO* ibo) {
		if (this->ibo)
			delete this->ibo;

		this->ibo = ibo;
	}

	void GLMesh::setIbo(uint32_t* indeces, uint32_t size) {
		if (ibo)
			delete ibo;

		ibo = new IBO(indeces, size);
	}

	void GLMesh::setTexture(GLTexture* tex) {
		if (this->tex)
			delete this->tex;

		this->tex = tex;
	}

	void GLMesh::setShader(GLShader* shader) {
		this->shader = shader;
	}

	void GLMesh::setModelMatrix(const glm::mat4& m) {
		modelMatrix = m;
	}

	bool GLMesh::checkCollision(const GLMesh& other) const {
		
		int oSize = 0;
		glm::vec2* oPos = other.getPositionsTranslated(oSize);

		int size = 0;
		glm::vec2* pos = getPositionsTranslated(size);
		
		static bool isDebug = false;
		if (debug)
			isDebug = true;
		for (int i = 0; i < size; i++) {
				
			glm::vec2 a1 = pos[i];
			glm::vec2 b1 = pos[(i == size - 1) ? 0 : i + 1];
			
			for (int j = 0; j < oSize; j++) {
			
				glm::vec2 a2 = oPos[j];
				glm::vec2 b2 = oPos[(j == oSize - 1) ? 0 : j + 1];
				
				SOE2 soe(a1, b1, a2, b2);
				
				if (soe.solve(isDebug))
					return true;
			}
			if (isDebug) isDebug = false;
		}

		delete pos;
		delete oPos;

		return false;
	}

	glm::vec2* GLMesh::getPositionsTranslated(int& out_size) const {

		out_size = vbo->getSize();
		Vertex* verteces = vbo->getData();
		glm::vec2* positions = new glm::vec2[out_size];

		glm::vec4 pos = modelMatrix[3];

		for (int i = 0; i < out_size; i++) {
			positions[i] = glm::vec2(modelMatrix[3] + glm::vec4(verteces[i].pos, 1.0f));
		}

		return positions;
	}

	void GLMesh::printMatrix() const {
		printf("Matrix:\n");
		for (int i = 0; i < 4; i++) {
			printf("%f\t%f\t%f\t%f\n", modelMatrix[i][0], modelMatrix[i][1], modelMatrix[i][2], modelMatrix[i][3]);
		}
		printf("----------------------\n");
	}

}