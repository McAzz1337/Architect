#include "glrenderer2d.h"
#include "glinclude.h"

#include "glrenderapi.h"

#include "glshaderconstants.h"

namespace archt {

	const int GLRenderer2D::MAX_OBJECTS = 1000;
	const int GLRenderer2D::MAX_VERTECES = 4 * MAX_OBJECTS;
	const int GLRenderer2D::MAX_INDECES = 6 * MAX_OBJECTS;


	uint32_t GLRenderer2D::currentVertex = 0;
	uint32_t GLRenderer2D::currentIndex = 0;
	int GLRenderer2D::currentTexture = 0;
	uint32_t GLRenderer2D::currentMatrix = 0;
	uint32_t GLRenderer2D::currentMesh = 0;

	GLShader* GLRenderer2D::activeShader = nullptr;

	bool GLRenderer2D::inScene = false;

	VBO* GLRenderer2D::vbo = nullptr;
	IBO* GLRenderer2D::ibo = nullptr;
	GLVertexarray* GLRenderer2D::vao = nullptr;

	std::vector<GLMesh*> GLRenderer2D::meshes;
	std::vector<glm::mat4> GLRenderer2D::matrices;
	std::vector<GLTexture*> GLRenderer2D::textures;



	Camera* GLRenderer2D::cam = nullptr;

	void GLRenderer2D::init() {

		meshes.reserve(MAX_OBJECTS);
		for (int i = 0; i < MAX_OBJECTS; i++) {
			meshes.push_back(nullptr);
		}


		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

		GLRenderAPI::enable(GL_DEPTH_TEST);
		GLRenderAPI::enable(GL_BLEND);
		
		GLRenderAPI::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		GLRenderAPI::setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLRenderAPI::setCullFace(GL_CW, GL_BACK);

		Vertex* verteces = new Vertex[MAX_VERTECES];
		vbo = new VBO(verteces, MAX_VERTECES);
		vbo->allocateOnGPU();

		uint32_t* indeces = new uint32_t[MAX_INDECES];
		ibo = new IBO(indeces, MAX_INDECES);
		ibo->allocateOnGPU();

		vao = new GLVertexarray(vbo, ibo);

		matrices.reserve(GLRenderAPI::maxMatrices);
		matrices.resize(GLRenderAPI::maxMatrices);

		int maxTextures = GLRenderAPI::getMaxTextureCount();
		textures.reserve(GLRenderAPI::maxTextures);
		textures.resize(GLRenderAPI::maxTextures);
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

		activeShader = meshes[0]->getShader();
		const glm::mat4 projectionView = cam->getProjectionView();

		for (int i = 0; i < currentMesh; i++) {

			GLMesh* mesh = meshes[i];

			VBO* vb = mesh->getVBO();
			IBO* ib = mesh->getIBO();

			uint32_t vSize = vb->getSize();
			uint32_t iSize = ib->getSize();

			GLTexture* tex = mesh->getTexture();

			if (currentVertex + vSize >= MAX_VERTECES ||
				currentIndex + iSize >= MAX_INDECES ||
				(!hasTexture(tex) && currentTexture == GLRenderAPI::maxTextures) ||
				currentMatrix == GLRenderAPI::maxMatrices ||
				mesh->getShader() != activeShader) {

				draw();
				flush();
				endBatch();

				activeShader = mesh->getShader();
			}

			tex->bind(currentTexture);
			vb->setTexId((float) currentTexture);
			textures[currentTexture] = tex;

			vb->setMatrixId((float) currentMatrix);
			matrices[currentMatrix] = (projectionView * mesh->getModelMatrix());

			vbo->write(currentVertex, vb->getData(), vSize);
			ibo->write(currentIndex, ib->getData(), iSize, currentVertex);

			currentVertex += vSize;
			currentIndex += iSize;
			currentTexture++;
			currentMatrix++;
		}

	}

	void GLRenderer2D::endBatch() {
		currentMesh = 0;
	}

	void GLRenderer2D::sort() {

		int index = 0;
		for (int i = 0; i < currentMesh - 1; i++) {
			GLShader* currentShader = meshes[i]->getShader();
			GLShader* nextShader = meshes[i + 1]->getShader();
			if (nextShader != currentShader) {
				index = i + 1;
				for (int j = i + 2; j < meshes.size(); j++) {
					nextShader = meshes[j]->getShader();
					if (nextShader == currentShader) {
						GLMesh* mesh = meshes[j];
						meshes[j] = meshes[index];
						meshes[index] = mesh;
						index++;
					}
				}
				i = index;
			}
		}
	}


	void GLRenderer2D::render() {
		if (!inScene || currentMesh == 0)
			return;

		sort();
		startBatch();
		draw();
		endBatch();
	}

	void GLRenderer2D::draw() {

		vbo->bind();
		ibo->bind();

		vbo->upload();
		ibo->upload();
		vao->bind();

		activeShader->bind();
		activeShader->setMatrixf4v("mvp", matrices.data(), currentMatrix);

		glDrawElements(GL_TRIANGLES, currentIndex, GL_UNSIGNED_INT, nullptr);
	}

	void GLRenderer2D::flush() {
		currentVertex = 0;
		currentIndex = 0;
		currentTexture = 0;
		currentMatrix = 0;
	}

	bool GLRenderer2D::hasTexture(GLTexture* tex) {

		for (int i = 0; i < currentTexture; i++) {
			if (textures[i] == tex)
				return true;
		}

		return false;
	}



}