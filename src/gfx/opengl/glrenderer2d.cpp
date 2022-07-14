#include "glrenderer2d.h"
#include "glinclude.h"

#include "glrenderapi.h"

namespace archt {



	const int GLRenderer2D::MAX_QUADS = 1000;
	const int GLRenderer2D::MAX_VERTECES = 4 * MAX_QUADS;
	const int GLRenderer2D::MAX_INDECES = 6 * MAX_QUADS;

	uint32_t GLRenderer2D::currentVertex = 0;
	uint32_t GLRenderer2D::currentIndex = 0;

	bool GLRenderer2D::inScene = false;

	VBO* GLRenderer2D::vbo = nullptr;
	IBO* GLRenderer2D::ibo = nullptr;
	GLVertexarray* GLRenderer2D::vao = nullptr;

	Camera* GLRenderer2D::cam = nullptr;

	void GLRenderer2D::init() {
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		GLRenderAPI::enable(GL_DEPTH_TEST);
		GLRenderAPI::setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glEnable(GL_DEPTH_TEST);
		glFrontFace(GL_CW); 
		glCullFace(GL_BACK);

		Vertex* verteces = new Vertex[MAX_VERTECES];
		for (int i = 0; i < MAX_VERTECES; i += 4) {
			verteces[i].pos =		{ -0.5f,  0.5f, 0.0f };
			verteces[i + 1].pos =	{ 0.5f,  0.5f, 0.0f };
			verteces[i + 2].pos =	{ 0.5f,  -0.5f, 0.0f };
			verteces[i + 3].pos =	{ -0.5f,  -0.5f, 0.0f };
		}

		vbo = new VBO(verteces, MAX_VERTECES);
		vbo->allocateOnGPU();

		uint32_t* indeces = new uint32_t[MAX_INDECES];
		int j = 0;
		for (int i = 0; i < MAX_INDECES; i += 6) {
			indeces[i] =		j;
			indeces[i + 1] =	j + 1;
			indeces[i + 2] =	j + 2;
			indeces[i + 3] =	j;
			indeces[i + 1] =	j + 2;
			indeces[i + 2] =	j + 3;

			j += 4;
		}
		
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

	void GLRenderer2D::submit(VBO* v, IBO* i) {
		if (!inScene)
			return;

		uint32_t vSize = v->getSize();
		uint32_t iSize = i->getSize();


		if (currentVertex + vSize >= MAX_VERTECES || currentIndex + iSize >= MAX_INDECES) {
			render();
			flush();
		}

		vbo->write(currentVertex, v->getData(), vSize);
		ibo->write(currentIndex, i->getData(), iSize);

		currentVertex += vSize;
		currentIndex += iSize;
	}


	void GLRenderer2D::clear() {
		glClear(GLRenderAPI::clearMask);
	}

	void GLRenderer2D::render() {
		if (!inScene)
			return;

		vbo->upload(GL_DYNAMIC_DRAW);
		ibo->upload(GL_DYNAMIC_DRAW);

		vao->bind();

		glDrawElements(GL_TRIANGLES, currentIndex, GL_UNSIGNED_INT, nullptr);

	}

	void GLRenderer2D::flush() {
		currentVertex = 0;
		currentIndex = 0;
	}




}