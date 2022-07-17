#pragma once

#include "glmesh.h"
#include "buffers.h"
#include "glvertexarray.h"
#include "camera.h"

#include <vector>
#include <typeindex>

namespace archt {

	class GLRenderer2D {

		const static int MAX_QUADS;
		const static int MAX_VERTECES;
		const static int MAX_INDECES;

		static int maxTextures;

		static uint32_t currentVertex;
		static uint32_t currentIndex;
		static uint32_t currentTexture;
		static uint32_t currentMesh;

		static bool inScene;
		static VBO* vbo;
		static IBO* ibo;
		static GLVertexarray* vao;
		static Camera* cam;
		static GLTexture* texture;
		static std::vector<GLMesh*> meshes;

	public:
		GLRenderer2D() = delete;
		static void init();
		static void terminate();

		static void beginScene(Camera* camera);
		static void endScene();

		static void submit(GLMesh* meh);

		static void clear();
		static void startBatch();
		static void endBatch();

		static void render();
		static void draw();
		static void flush();


	};


}