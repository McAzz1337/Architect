#include "glrenderer2d.h"
#include "glinclude.h"

#include "glrenderapi.h"

#include "glshaderconstants.h"

namespace archt {



	const int GLRenderer2D::MAX_QUADS = 1000;
	const int GLRenderer2D::MAX_VERTECES = 4 * MAX_QUADS;
	const int GLRenderer2D::MAX_INDECES = 6 * MAX_QUADS;


	uint32_t GLRenderer2D::currentVertex = 0;
	uint32_t GLRenderer2D::currentIndex = 0;
	uint32_t GLRenderer2D::currentTexture = 0;
	uint32_t GLRenderer2D::currentMesh = 0;

	bool GLRenderer2D::inScene = false;

	VBO* GLRenderer2D::vbo = nullptr;
	IBO* GLRenderer2D::ibo = nullptr;
	GLVertexarray* GLRenderer2D::vao = nullptr;
	GLTexture* GLRenderer2D::texture = nullptr;

	std::vector<GLMesh*> GLRenderer2D::meshes;


	Camera* GLRenderer2D::cam = nullptr;

	void GLRenderer2D::init() {

		meshes.reserve(MAX_QUADS);
		for (int i = 0; i < MAX_QUADS; i++) {
			meshes.push_back(nullptr);
		}
	

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		GLRenderAPI::enable(GL_DEPTH_TEST);
		GLRenderAPI::enable(GL_BLEND);
		GLRenderAPI::setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLRenderAPI::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLRenderAPI::enable(GL_CULL_FACE);
		glFrontFace(GL_CW); 
		glCullFace(GL_BACK);

		Vertex* verteces = new Vertex[MAX_VERTECES];
		vbo = new VBO(verteces, MAX_VERTECES);
		vbo->allocateOnGPU();

		uint32_t* indeces = new uint32_t[MAX_INDECES];
		ibo = new IBO(indeces, MAX_INDECES);
		ibo->allocateOnGPU();

		vao = new GLVertexarray(vbo, ibo);
	}

	void GLRenderer2D::terminate() {
		delete ibo;
		delete vbo;
		delete vao;
	}

	void GLRenderer2D::beginScene(Camera* camera) {
		inScene = true;
		cam = camera;
	}
	void GLRenderer2D::endScene() {
		inScene = false;

	}

	void GLRenderer2D::submit(GLMesh* mesh) {
		if (!inScene)
			return;

		meshes[currentMesh] = mesh;
		currentMesh++;
	}


	void GLRenderer2D::clear() {
		glClear(GLRenderAPI::clearMask);
	}

	void GLRenderer2D::startBatch() {
		
		static bool printed = false;

		meshes[0]->getShader()->bind();
		uint32_t maxTextures = GLRenderAPI::getMaxTextureCount();
		for (int i = 0; i < currentMesh; i++) {

			VBO* vb = meshes[i]->getVBO();
			IBO* ib = meshes[i]->getIBO();

			uint32_t vSize = vb->getSize();
			uint32_t iSize = ib->getSize();

			if (currentVertex + vSize >= MAX_VERTECES || 
				currentIndex + iSize >= MAX_INDECES ||
				currentTexture == maxTextures) {
				draw();
				flush();
				endBatch();
			}
			
			meshes[i]->getTexture()->bind(currentTexture);
			vb->setTexId((float)currentTexture);
			
			if (!printed && currentTexture == 1) {
				vb->print(vb->getSize());
				printed = true;
			}

			vbo->write(currentVertex, vb->getData(), vSize);
			ibo->write(currentIndex, ib->getData(), iSize);
			
			currentVertex += vSize;
			currentIndex += iSize;
			currentTexture++;
		}

		if (!printed) {
			vbo->print(currentVertex);
			printed = true;
		}
	}

	void GLRenderer2D::endBatch() {
		currentMesh = 0;
	}

	void GLRenderer2D::render() {
		if (!inScene)
			return;

		startBatch();
		draw();
		endBatch();
	}

	void GLRenderer2D::draw() {
		
		vbo->upload(GL_DYNAMIC_DRAW);
		ibo->upload(GL_DYNAMIC_DRAW);
		vao->bind();

		glDrawElements(GL_TRIANGLES, currentIndex, GL_UNSIGNED_INT, nullptr);
	}

	void GLRenderer2D::flush() {
		currentVertex = 0;
		currentIndex = 0;
		currentTexture = 0;
	}




}