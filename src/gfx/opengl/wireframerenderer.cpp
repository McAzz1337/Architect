#include "wireframerenderer.h"

namespace archt {

	const int WireframeRenderer::MAX_OBJECTS = 1000;
	const int WireframeRenderer::MAX_VERTECES = 4 * MAX_OBJECTS;
	const int WireframeRenderer::MAX_INDECES = 6 * MAX_OBJECTS;

	Camera* WireframeRenderer::cam = nullptr;

	int WireframeRenderer::currentMesh = 0;
	GLMesh** WireframeRenderer::meshes = nullptr;
	int WireframeRenderer::currentMatrix = 0;
	glm::mat4* WireframeRenderer::matrices = nullptr;
	glm::vec4* WireframeRenderer::colors = nullptr;


	uint32_t WireframeRenderer::currentVertex = 0;
	uint32_t WireframeRenderer::currentIndex = 0;

	VBO* WireframeRenderer::vbo = nullptr;
	IBO* WireframeRenderer::ibo = nullptr;
	GLVertexarray* WireframeRenderer::vao = nullptr;

	GLShader* WireframeRenderer::shader = nullptr;


	void WireframeRenderer::init() {

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		meshes = new GLMesh * [MAX_OBJECTS];
		for (int i = 0; i < MAX_OBJECTS; i++) {
			meshes[i] = nullptr;
		}

		matrices = new glm::mat4[MAX_OBJECTS];
		colors = new glm::vec4[MAX_OBJECTS];

		Vertex* verteces = new Vertex[MAX_VERTECES];
		vbo = new VBO(verteces, MAX_VERTECES);
		vbo->allocateOnGPU(MAX_VERTECES, GL_DYNAMIC_DRAW);

		uint32_t* indeces = new uint32_t[MAX_INDECES];
		ibo = new IBO(indeces, MAX_INDECES);
		ibo->allocateOnGPU(MAX_INDECES, GL_DYNAMIC_DRAW);

		vao = new GLVertexarray(vbo, ibo, false);
		vao->setVertexAttribPointer(0, 3, (const void*) offsetof(Vertex, pos));
		vao->setVertexAttribPointer(1, 1, (const void*) offsetof(Vertex, texId));
		vao->setVertexAttribPointer(2, 1, (const void*) offsetof(Vertex, matrixId));


		shader = new GLShader("src/assets/shaders/wireframeshader/wireframeshader");
		Uniformbuffer* mats = new Uniformbuffer("matrices", nullptr, 4 * 16 * MAX_OBJECTS, 0);
		Uniformbuffer* colrs = new Uniformbuffer("colors", nullptr, 4 * MAX_OBJECTS, 1);

		shader->registerUniformBuffer(mats);
		shader->registerUniformBuffer(colrs);
	}

	void WireframeRenderer::terminate() {
		delete shader;

		delete[] matrices;
		delete[] meshes;
		delete[] colors;

		delete ibo;
		delete vbo;
		delete vao;
	}

	void WireframeRenderer::clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void WireframeRenderer::submit(GLMesh* mesh, glm::vec4 color) {

		if (currentMesh == MAX_OBJECTS) {
			render();
			endScene();
			beginScene(cam);
		}

		meshes[currentMesh] = mesh;
		colors[currentMesh] = color;

		currentMesh++;
	}

	void WireframeRenderer::beginScene(Camera* camera) {
		cam = camera;
	}

	void WireframeRenderer::endScene() {
		currentMesh = 0;
	}

	uint32_t* WireframeRenderer::reorderIndeces(uint32_t* src, uint32_t size) {

		uint32_t* dst = new uint32_t[8]{
			0, 1, 1, 2, 2, 3, 3, 0
		};

		//int j = 0;
		//for (int i = 0; i < size - 3; i += 3) {
		//	dst[j] = src[i];
		//	dst[j + 1] = src[i + 1];
		//	dst[j + 2] = src[i + 1];
		//	dst[j + 3] = src[i + 2];
		//	j += 4;
		//}

		return dst;
	}


	void WireframeRenderer::beginBatch() {

		glm::mat4 projectionView = cam->getProjectionView();

		for (int i = 0; i < currentMesh; i++) {

			GLMesh* mesh = meshes[i];

			VBO* vb = mesh->getVBO();
			IBO* ib = mesh->getIBO();

			uint32_t vSize = vb->getSize();
			uint32_t iSize = ib->getSize();


			matrices[currentMatrix] = projectionView * mesh->getModelMatrix();
			vb->setMatrixId((float) currentMatrix);
			currentMatrix++;

			vb->setTexId((float) i);

			uint32_t* indeces = reorderIndeces(ib->getData(), iSize);

			vbo->write(currentVertex, vb->getData(), vSize);
			ibo->write(currentIndex, indeces, 8, currentVertex);

			currentVertex += vSize;
			currentIndex += 8;
		}
	}

	void WireframeRenderer::endBatch() {
		currentMatrix = 0;
	}

	void WireframeRenderer::render() {

		beginBatch();
		draw();
		endBatch();
		flush();
	}

	void WireframeRenderer::draw() {

		vbo->bind();
		ibo->bind();

		vbo->upload();
		ibo->upload();

		vao->bind();

		shader->bind();

		const std::vector<Uniformbuffer*> buffers = shader->getUniformBuffers();

		for (int i = 0; i < buffers.size(); i++) {
			buffers[i]->bind();
			if (buffers[i]->getName() == "matrices") {
				buffers[i]->write(0, matrices, currentMatrix * sizeof(glm::mat4));
			}
			else if (buffers[i]->getName() == "colors") {
				buffers[i]->write(0, colors, currentMesh * sizeof(glm::vec4));
			}
			buffers[i]->upload();
		}



		glDrawElements(GL_LINES, currentIndex, GL_UNSIGNED_INT, nullptr);
	}


	void WireframeRenderer::flush() {
		currentVertex = 0;
		currentIndex = 0;
	}
}